pm80xx_chip_soft_rst(struct pm8001_hba_info *pm8001_ha)
{
	u32 regval;
	u32 bootloader_state;
	u32 ibutton0, ibutton1;


	if (mpi_uninit_check(pm8001_ha) != 0) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("MPI state is not ready\n"));
		return -1;
	}


	regval = pm8001_cr32(pm8001_ha, 0, SPC_REG_SOFT_RESET);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("reset register before write : 0x%x\n", regval));

	pm8001_cw32(pm8001_ha, 0, SPC_REG_SOFT_RESET, SPCv_NORMAL_RESET_VALUE);
	mdelay(500);

	regval = pm8001_cr32(pm8001_ha, 0, SPC_REG_SOFT_RESET);
	PM8001_INIT_DBG(pm8001_ha,
	pm8001_printk("reset register after write 0x%x\n", regval));

	if ((regval & SPCv_SOFT_RESET_READ_MASK) ==
			SPCv_SOFT_RESET_NORMAL_RESET_OCCURED) {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(" soft reset successful [regval: 0x%x]\n",
					regval));
	} else {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(" soft reset failed [regval: 0x%x]\n",
					regval));


		bootloader_state =
			pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1) &
			SCRATCH_PAD1_BOOTSTATE_MASK;

		if (bootloader_state == SCRATCH_PAD1_BOOTSTATE_HDA_SEEPROM) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state - HDA mode SEEPROM\n"));
		} else if (bootloader_state ==
				SCRATCH_PAD1_BOOTSTATE_HDA_BOOTSTRAP) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state - HDA mode Bootstrap Pin\n"));
		} else if (bootloader_state ==
				SCRATCH_PAD1_BOOTSTATE_HDA_SOFTRESET) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state - HDA mode soft reset\n"));
		} else if (bootloader_state ==
					SCRATCH_PAD1_BOOTSTATE_CRIT_ERROR) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state-HDA mode critical error\n"));
		}
		return -EBUSY;
	}


	if (-1 == check_fw_ready(pm8001_ha)) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Firmware is not ready!\n"));

		if (pm8001_ha->pdev->subsystem_vendor !=
			PCI_VENDOR_ID_ADAPTEC2 &&
			pm8001_ha->pdev->subsystem_vendor !=
			PCI_VENDOR_ID_ATTO &&
			pm8001_ha->pdev->subsystem_vendor != 0) {
			ibutton0 = pm8001_cr32(pm8001_ha, 0,
					MSGU_HOST_SCRATCH_PAD_6);
			ibutton1 = pm8001_cr32(pm8001_ha, 0,
					MSGU_HOST_SCRATCH_PAD_7);
			if (!ibutton0 && !ibutton1) {
				PM8001_FAIL_DBG(pm8001_ha,
					pm8001_printk("iButton Feature is"
					" not Available!!!\n"));
				return -EBUSY;
			}
			if (ibutton0 == 0xdeadbeef && ibutton1 == 0xdeadbeef) {
				PM8001_FAIL_DBG(pm8001_ha,
					pm8001_printk("CRC Check for iButton"
					" Feature Failed!!!\n"));
				return -EBUSY;
			}
		}
	}
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("SPCv soft reset Complete\n"));
	return 0;
}
