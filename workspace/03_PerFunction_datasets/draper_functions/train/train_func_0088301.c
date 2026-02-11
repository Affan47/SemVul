snd_aw2_control_switch_capture_get(struct snd_kcontrol *kcontrol,
					      struct snd_ctl_elem_value
					      *ucontrol)
{
	struct aw2 *chip = snd_kcontrol_chip(kcontrol);
	if (snd_aw2_saa7146_is_using_digital_input(&chip->saa7146))
		ucontrol->value.enumerated.item[0] = CTL_ROUTE_DIGITAL;
	else
		ucontrol->value.enumerated.item[0] = CTL_ROUTE_ANALOG;
	return 0;
}
