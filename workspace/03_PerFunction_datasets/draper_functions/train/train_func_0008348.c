mt7601u_set_bw_filter(struct mt7601u_dev *dev, bool cal)
{
	u32 filter = 0;
	int ret;

	if (!cal)
		filter |= 0x10000;
	if (dev->bw != MT_BW_20)
		filter |= 0x00100;


	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_BW, filter | 1);
	if (ret)
		return ret;

	return mt7601u_mcu_calibrate(dev, MCU_CAL_BW, filter);
}
