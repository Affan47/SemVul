nvt_resume(struct pnp_dev *pdev)
{
	struct nvt_dev *nvt = pnp_get_drvdata(pdev);

	nvt_dbg("%s called", __func__);


	nvt_set_cir_iren(nvt);


	nvt_efm_enable(nvt);
	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR);
	nvt_cr_write(nvt, LOGICAL_DEV_ENABLE, CR_LOGICAL_DEV_EN);

	nvt_efm_disable(nvt);

	nvt_cir_regs_init(nvt);
	nvt_cir_wake_regs_init(nvt);

	return 0;
}
