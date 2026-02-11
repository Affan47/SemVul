dfc_put_byte(uaecptr addr, uae_u8 val)
{
	int super = (regs.dfc & 4) != 0;
	int data = (regs.dfc & 3) != 2;

	SAVE_EXCEPTION;
	TRY(prb) {
		mmu_put_user_byte(addr, val, super, data, sz_byte);
		RESTORE_EXCEPTION;
	}
	CATCH(prb) {
		RESTORE_EXCEPTION;
		regs.wb3_data = val;
		THROW_AGAIN(prb);
	}
}
