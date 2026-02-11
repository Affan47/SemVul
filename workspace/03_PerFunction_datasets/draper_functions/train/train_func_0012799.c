bfa_ioc_boot(struct bfa_ioc_s *ioc, u32 boot_type, u32 boot_env)
{
	struct bfi_ioc_image_hdr_s *drv_fwhdr;
	bfa_status_t status;
	bfa_ioc_stats(ioc, ioc_boots);

	if (bfa_ioc_pll_init(ioc) != BFA_STATUS_OK)
		return BFA_STATUS_FAILED;

	if (boot_env == BFI_FWBOOT_ENV_OS &&
		boot_type == BFI_FWBOOT_TYPE_NORMAL) {

		drv_fwhdr = (struct bfi_ioc_image_hdr_s *)
			bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);


		if (bfa_ioc_flash_fwver_cmp(ioc, drv_fwhdr) ==
						BFI_IOC_IMG_VER_BETTER)
			boot_type = BFI_FWBOOT_TYPE_FLASH;
	}


	if (boot_type == BFI_FWBOOT_TYPE_MEMTEST) {
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_MEMTEST);
		bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_MEMTEST);
	} else {
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_INITING);
		bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_INITING);
	}

	bfa_ioc_msgflush(ioc);
	status = bfa_ioc_download_fw(ioc, boot_type, boot_env);
	if (status == BFA_STATUS_OK)
		bfa_ioc_lpu_start(ioc);
	else {
		WARN_ON(boot_type == BFI_FWBOOT_TYPE_MEMTEST);
		bfa_iocpf_timeout(ioc);
	}
	return status;
}
