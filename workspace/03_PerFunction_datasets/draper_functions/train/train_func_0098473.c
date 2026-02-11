m88rs6000t_set_bb(struct m88rs6000t_dev *dev,
		u32 symbol_rate_KSs, s32 lpf_offset_KHz)
{
	u32 f3dB;
	u8  reg40;

	f3dB = symbol_rate_KSs * 9 / 14 + 2000;
	f3dB += lpf_offset_KHz;
	f3dB = clamp_val(f3dB, 6000U, 43000U);
	reg40 = f3dB / 1000;
	return regmap_write(dev->regmap, 0x40, reg40);
}
