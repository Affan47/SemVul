tsi568_em_init(struct rio_dev *rdev)
{
	u32 regval;
	int portnum;

	pr_debug("TSI568 %s [%d:%d]\n", __func__, rdev->destid, rdev->hopcount);


	for (portnum = 0;
	     portnum < RIO_GET_TOTAL_PORTS(rdev->swpinfo); portnum++) {
		rio_read_config_32(rdev, TSI568_SP_MODE(portnum), &regval);
		rio_write_config_32(rdev, TSI568_SP_MODE(portnum),
				    regval | TSI568_SP_MODE_PW_DIS);
	}

	return 0;
}
