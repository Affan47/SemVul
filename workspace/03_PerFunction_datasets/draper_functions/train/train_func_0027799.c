bnad_flash_device(struct net_device *netdev, struct ethtool_flash *eflash)
{
	struct bnad *bnad = netdev_priv(netdev);
	struct bnad_iocmd_comp fcomp;
	const struct firmware *fw;
	int ret = 0;

	ret = request_firmware(&fw, eflash->data, &bnad->pcidev->dev);
	if (ret) {
		netdev_err(netdev, "can't load firmware %s\n", eflash->data);
		goto out;
	}

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irq(&bnad->bna_lock);
	ret = bfa_nw_flash_update_part(&bnad->bna.flash, BFA_FLASH_PART_FWIMG,
				bnad->id, (u8 *)fw->data, fw->size, 0,
				bnad_cb_completion, &fcomp);
	if (ret != BFA_STATUS_OK) {
		netdev_warn(netdev, "flash update failed with err=%d\n", ret);
		ret = -EIO;
		spin_unlock_irq(&bnad->bna_lock);
		goto out;
	}

	spin_unlock_irq(&bnad->bna_lock);
	wait_for_completion(&fcomp.comp);
	if (fcomp.comp_status != BFA_STATUS_OK) {
		ret = -EIO;
		netdev_warn(netdev,
			    "firmware image update failed with err=%d\n",
			    fcomp.comp_status);
	}
out:
	release_firmware(fw);
	return ret;
}
