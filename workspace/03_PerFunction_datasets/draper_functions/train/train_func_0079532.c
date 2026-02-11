phase22_add_controls(struct snd_ice1712 *ice)
{
	int err = 0;

	switch (ice->eeprom.subvendor) {
	case VT1724_SUBDEVICE_PHASE22:
	case VT1724_SUBDEVICE_TS22:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		if (err < 0)
			return err;
	}
	return 0;
}
