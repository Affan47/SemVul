bnad_get_eeprom(struct net_device *netdev, struct ethtool_eeprom *eeprom,
		u8 *bytes)
{
	struct bnad *bnad = netdev_priv(netdev);
	struct bnad_iocmd_comp fcomp;
	u32 flash_part = 0, base_offset = 0;
	unsigned long flags = 0;
	int ret = 0;


	eeprom->magic = bnad->pcidev->vendor | (bnad->pcidev->device << 16);


	flash_part = bnad_get_flash_partition_by_offset(bnad,
				eeprom->offset, &base_offset);
	if (flash_part == 0)
		return -EFAULT;

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_flash_read_part(&bnad->bna.flash, flash_part,
				bnad->id, bytes, eeprom->len,
				eeprom->offset - base_offset,
				bnad_cb_completion, &fcomp);
	if (ret != BFA_STATUS_OK) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		goto done;
	}

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	wait_for_completion(&fcomp.comp);
	ret = fcomp.comp_status;
done:
	return ret;
}
