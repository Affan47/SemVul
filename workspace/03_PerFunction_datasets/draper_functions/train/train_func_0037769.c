myri10ge_select_firmware(struct myri10ge_priv *mgp)
{
	int overridden = 0;

	if (myri10ge_force_firmware == 0) {
		int link_width;
		u16 lnk;

		pcie_capability_read_word(mgp->pdev, PCI_EXP_LNKSTA, &lnk);
		link_width = (lnk >> 4) & 0x3f;


		if (link_width < 8) {
			dev_info(&mgp->pdev->dev, "PCIE x%d Link\n",
				 link_width);
			mgp->tx_boundary = 4096;
			set_fw_name(mgp, myri10ge_fw_aligned, false);
		} else {
			myri10ge_firmware_probe(mgp);
		}
	} else {
		if (myri10ge_force_firmware == 1) {
			dev_info(&mgp->pdev->dev,
				 "Assuming aligned completions (forced)\n");
			mgp->tx_boundary = 4096;
			set_fw_name(mgp, myri10ge_fw_aligned, false);
		} else {
			dev_info(&mgp->pdev->dev,
				 "Assuming unaligned completions (forced)\n");
			mgp->tx_boundary = 2048;
			set_fw_name(mgp, myri10ge_fw_unaligned, false);
		}
	}

	kernel_param_lock(THIS_MODULE);
	if (myri10ge_fw_name != NULL) {
		char *fw_name = kstrdup(myri10ge_fw_name, GFP_KERNEL);
		if (fw_name) {
			overridden = 1;
			set_fw_name(mgp, fw_name, true);
		}
	}
	kernel_param_unlock(THIS_MODULE);

	if (mgp->board_number < MYRI10GE_MAX_BOARDS &&
	    myri10ge_fw_names[mgp->board_number] != NULL &&
	    strlen(myri10ge_fw_names[mgp->board_number])) {
		set_fw_name(mgp, myri10ge_fw_names[mgp->board_number], false);
		overridden = 1;
	}
	if (overridden)
		dev_info(&mgp->pdev->dev, "overriding firmware to %s\n",
			 mgp->fw_name);
}
