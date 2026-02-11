sfc_get_word(uaecptr addr)
{
	bool super = (regs.sfc & 4) != 0;
	bool data = (regs.sfc & 3) != 2;
	uae_u16 res;

	if (likely(!is_unaligned(addr, 2)))
		return mmu_get_user_word(addr, super, data, sz_word);

	res = (uae_u16)mmu_get_user_byte(addr, super, data, sz_word) << 8;
	SAVE_EXCEPTION;
	TRY(prb) {
		res |= mmu_get_user_byte(addr + 1, super, data, sz_word);
		RESTORE_EXCEPTION;
	}
	CATCH(prb) {
		RESTORE_EXCEPTION;
		regs.mmu_fault_addr = addr;
		regs.mmu_ssw |= MMU_SSW_MA;
		THROW_AGAIN(prb);
	}
	return res;
}
