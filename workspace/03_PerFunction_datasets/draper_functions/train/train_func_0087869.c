__adf_iov_putmsg(struct adf_accel_dev *accel_dev, u32 msg, u8 vf_nr)
{
	struct adf_accel_pci *pci_info = &accel_dev->accel_pci_dev;
	struct adf_hw_device_data *hw_data = accel_dev->hw_device;
	void __iomem *pmisc_bar_addr =
		pci_info->pci_bars[hw_data->get_misc_bar_id(hw_data)].virt_addr;
	u32 val, pf2vf_offset, count = 0;
	u32 local_in_use_mask, local_in_use_pattern;
	u32 remote_in_use_mask, remote_in_use_pattern;
	struct mutex *lock;
	u32 int_bit;
	int ret = 0;

	if (accel_dev->is_vf) {
		pf2vf_offset = hw_data->get_pf2vf_offset(0);
		lock = &accel_dev->vf.vf2pf_lock;
		local_in_use_mask = ADF_VF2PF_IN_USE_BY_VF_MASK;
		local_in_use_pattern = ADF_VF2PF_IN_USE_BY_VF;
		remote_in_use_mask = ADF_PF2VF_IN_USE_BY_PF_MASK;
		remote_in_use_pattern = ADF_PF2VF_IN_USE_BY_PF;
		int_bit = ADF_VF2PF_INT;
	} else {
		pf2vf_offset = hw_data->get_pf2vf_offset(vf_nr);
		lock = &accel_dev->pf.vf_info[vf_nr].pf2vf_lock;
		local_in_use_mask = ADF_PF2VF_IN_USE_BY_PF_MASK;
		local_in_use_pattern = ADF_PF2VF_IN_USE_BY_PF;
		remote_in_use_mask = ADF_VF2PF_IN_USE_BY_VF_MASK;
		remote_in_use_pattern = ADF_VF2PF_IN_USE_BY_VF;
		int_bit = ADF_PF2VF_INT;
	}

	mutex_lock(lock);


	val = ADF_CSR_RD(pmisc_bar_addr, pf2vf_offset);
	if ((val & remote_in_use_mask) == remote_in_use_pattern) {
		dev_dbg(&GET_DEV(accel_dev),
			"PF2VF CSR in use by remote function\n");
		ret = -EBUSY;
		goto out;
	}


	msg &= ~local_in_use_mask;
	msg |= local_in_use_pattern;
	ADF_CSR_WR(pmisc_bar_addr, pf2vf_offset, msg);


	msleep(ADF_IOV_MSG_COLLISION_DETECT_DELAY);

	val = ADF_CSR_RD(pmisc_bar_addr, pf2vf_offset);
	if ((val & local_in_use_mask) != local_in_use_pattern) {
		dev_dbg(&GET_DEV(accel_dev),
			"PF2VF CSR in use by remote - collision detected\n");
		ret = -EBUSY;
		goto out;
	}


	ADF_CSR_WR(pmisc_bar_addr, pf2vf_offset, msg | int_bit);


	do {
		msleep(ADF_IOV_MSG_ACK_DELAY);
		val = ADF_CSR_RD(pmisc_bar_addr, pf2vf_offset);
	} while ((val & int_bit) && (count++ < ADF_IOV_MSG_ACK_MAX_RETRY));

	if (val & int_bit) {
		dev_dbg(&GET_DEV(accel_dev), "ACK not received from remote\n");
		val &= ~int_bit;
		ret = -EIO;
	}


	ADF_CSR_WR(pmisc_bar_addr, pf2vf_offset, val & ~local_in_use_mask);
out:
	mutex_unlock(lock);
	return ret;
}
