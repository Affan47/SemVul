kioc_to_mimd(uioc_t *kioc, mimd_t __user *mimd)
{
	mimd_t			kmimd;
	uint8_t			opcode;
	uint8_t			subopcode;

	mbox64_t		*mbox64;
	mraid_passthru_t	__user *upthru32;
	mraid_passthru_t	*kpthru32;
	mcontroller_t		cinfo;
	mraid_hba_info_t	*hinfo;


	if (copy_from_user(&kmimd, mimd, sizeof(mimd_t)))
		return (-EFAULT);

	opcode		= kmimd.ui.fcs.opcode;
	subopcode	= kmimd.ui.fcs.subopcode;

	if (opcode == 0x82) {
		switch (subopcode) {

		case MEGAIOC_QADAPINFO:

			hinfo = (mraid_hba_info_t *)(unsigned long)
					kioc->buf_vaddr;

			hinfo_to_cinfo(hinfo, &cinfo);

			if (copy_to_user(kmimd.data, &cinfo, sizeof(cinfo)))
				return (-EFAULT);

			return 0;

		default:
			return (-EINVAL);
		}

		return 0;
	}

	mbox64 = (mbox64_t *)(unsigned long)kioc->cmdbuf;

	if (kioc->user_pthru) {

		upthru32 = kioc->user_pthru;
		kpthru32 = kioc->pthru32;

		if (copy_to_user(&upthru32->scsistatus,
					&kpthru32->scsistatus,
					sizeof(uint8_t))) {
			return (-EFAULT);
		}
	}

	if (kioc->user_data) {
		if (copy_to_user(kioc->user_data, kioc->buf_vaddr,
					kioc->user_data_len)) {
			return (-EFAULT);
		}
	}

	if (copy_to_user(&mimd->mbox[17],
			&mbox64->mbox32.status, sizeof(uint8_t))) {
		return (-EFAULT);
	}

	return 0;
}
