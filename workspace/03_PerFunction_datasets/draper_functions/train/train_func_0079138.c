bfa_flash_erase_part(struct bfa_flash_s *flash, enum bfa_flash_part_type type,
		u8 instance, bfa_cb_flash_t cbfn, void *cbarg)
{
	bfa_trc(flash, BFI_FLASH_H2I_ERASE_REQ);
	bfa_trc(flash, type);
	bfa_trc(flash, instance);

	if (!bfa_ioc_is_operational(flash->ioc))
		return BFA_STATUS_IOC_NON_OP;

	if (flash->op_busy) {
		bfa_trc(flash, flash->op_busy);
		return BFA_STATUS_DEVBUSY;
	}

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->type = type;
	flash->instance = instance;

	bfa_flash_erase_send(flash);
	bfa_flash_aen_audit_post(flash->ioc, BFA_AUDIT_AEN_FLASH_ERASE,
				instance, type);
	return BFA_STATUS_OK;
}
