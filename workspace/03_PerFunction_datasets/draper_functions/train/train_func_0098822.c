get_line_in_mode(struct cmipci *cm)
{
	unsigned int val;
	if (cm->chip_version >= 39) {
		val = snd_cmipci_read(cm, CM_REG_LEGACY_CTRL);
		if (val & (CM_CENTR2LIN | CM_BASE2LIN))
			return 2;
	}
	val = snd_cmipci_read_b(cm, CM_REG_MIXER1);
	if (val & CM_REAR2LIN)
		return 1;
	return 0;
}
