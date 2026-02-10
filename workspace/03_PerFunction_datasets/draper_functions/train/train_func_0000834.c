qlcnic_83xx_read_crb(struct qlcnic_adapter *adapter, char *buf,
			  loff_t offset, size_t size)
{
	int ret = 0;
	u32 data;

	if (qlcnic_api_lock(adapter)) {
		dev_err(&adapter->pdev->dev,
			"%s: failed to acquire lock. addr offset 0x%x\n",
			__func__, (u32)offset);
		return;
	}

	data = QLCRD32(adapter, (u32) offset, &ret);
	qlcnic_api_unlock(adapter);

	if (ret == -EIO) {
		dev_err(&adapter->pdev->dev,
			"%s: failed. addr offset 0x%x\n",
			__func__, (u32)offset);
		return;
	}
	memcpy(buf, &data, size);
}
