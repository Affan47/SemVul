vpfe_reg_dump(struct vpfe_ccdc *ccdc)
{
	struct vpfe_device *vpfe = to_vpfe(ccdc);

	vpfe_dbg(3, vpfe, "ALAW: 0x%x\n", vpfe_reg_read(ccdc, VPFE_ALAW));
	vpfe_dbg(3, vpfe, "CLAMP: 0x%x\n", vpfe_reg_read(ccdc, VPFE_CLAMP));
	vpfe_dbg(3, vpfe, "DCSUB: 0x%x\n", vpfe_reg_read(ccdc, VPFE_DCSUB));
	vpfe_dbg(3, vpfe, "BLKCMP: 0x%x\n", vpfe_reg_read(ccdc, VPFE_BLKCMP));
	vpfe_dbg(3, vpfe, "COLPTN: 0x%x\n", vpfe_reg_read(ccdc, VPFE_COLPTN));
	vpfe_dbg(3, vpfe, "SDOFST: 0x%x\n", vpfe_reg_read(ccdc, VPFE_SDOFST));
	vpfe_dbg(3, vpfe, "SYN_MODE: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_SYNMODE));
	vpfe_dbg(3, vpfe, "HSIZE_OFF: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_HSIZE_OFF));
	vpfe_dbg(3, vpfe, "HORZ_INFO: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_HORZ_INFO));
	vpfe_dbg(3, vpfe, "VERT_START: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_VERT_START));
	vpfe_dbg(3, vpfe, "VERT_LINES: 0x%x\n",
		 vpfe_reg_read(ccdc, VPFE_VERT_LINES));
}
