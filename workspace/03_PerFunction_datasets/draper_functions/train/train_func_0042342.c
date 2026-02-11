tsi721_dsend(struct rio_mport *mport, int index,
			u16 destid, u16 data)
{
	struct tsi721_device *priv = mport->priv;
	u32 offset;

	offset = (((mport->sys_size) ? RIO_TT_CODE_16 : RIO_TT_CODE_8) << 18) |
		 (destid << 2);

	dev_dbg(&priv->pdev->dev,
		"Send Doorbell 0x%04x to destID 0x%x\n", data, destid);
	iowrite16be(data, priv->odb_base + offset);

	return 0;
}
