bcm2048_get_rds_b_block_match(struct bcm2048_device *bdev)
{
	int err;
	u8 lsb = 0, msb = 0;

	mutex_lock(&bdev->mutex);

	err = bcm2048_recv_command(bdev,
			BCM2048_I2C_RDS_BLKB_MATCH0, &lsb);
	err |= bcm2048_recv_command(bdev,
			BCM2048_I2C_RDS_BLKB_MATCH1, &msb);

	mutex_unlock(&bdev->mutex);

	if (!err)
		return compose_u16(msb, lsb);

	return err;
}
