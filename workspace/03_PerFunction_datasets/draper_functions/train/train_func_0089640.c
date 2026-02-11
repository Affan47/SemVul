sfc_get_long(uaecptr addr)
{
	bool super = (regs.sfc & 4) != 0;
	bool data = (regs.sfc & 3) != 2;
	uae_u32 res;

	if (likely(!is_unaligned(addr, 4)))
		return mmu_get_user_long(addr, super, data, sz_long);

	if (likely(!(addr & 1))) {
		res = (uae_u32)mmu_get_user_word(addr, super, data, sz_long) << 16;
		SAVE_EXCEPTION;
		TRY(prb) {
			res |= mmu_get_user_word(addr + 2, super, data, sz_long);
			RESTORE_EXCEPTION;
		}
		CATCH(prb) {
			RESTORE_EXCEPTION;
			regs.mmu_fault_addr = addr;
			regs.mmu_ssw |= MMU_SSW_MA;
			THROW_AGAIN(prb);
		}
	} else {
		res = (uae_u32)mmu_get_user_byte(addr, super, data, sz_long) << 8;
		SAVE_EXCEPTION;
		TRY(prb) {
			res = (res | mmu_get_user_byte(addr + 1, super, data, sz_long)) << 8;
			res = (res | mmu_get_user_byte(addr + 2, super, data, sz_long)) << 8;
			res |= mmu_get_user_byte(addr + 3, super, data, sz_long);
			RESTORE_EXCEPTION;
		}
		CATCH(prb) {
			RESTORE_EXCEPTION;
			regs.mmu_fault_addr = addr;
			regs.mmu_ssw |= MMU_SSW_MA;
			THROW_AGAIN(prb);
		}
	}
	return res;
}
