put_ak_reg(struct snd_kcontrol *kcontrol, int addr,
		      unsigned char nval)
{
	struct snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	unsigned int mask = AK_GET_MASK(kcontrol->private_value);
	int chip = AK_GET_CHIP(kcontrol->private_value);

	if (snd_akm4xxx_get_vol(ak, chip, addr) == nval)
		return 0;

	snd_akm4xxx_set_vol(ak, chip, addr, nval);
	if (AK_GET_VOL_CVT(kcontrol->private_value) && nval < 128)
		nval = vol_cvt_datt[nval];
	if (AK_GET_IPGA(kcontrol->private_value) && nval >= 128)
		nval++;
	if (AK_GET_INVERT(kcontrol->private_value))
		nval = mask - nval;
	if (AK_GET_NEEDSMSB(kcontrol->private_value))
		nval |= 0x80;


	snd_akm4xxx_write(ak, chip, addr, nval);
	return 1;
}
