snd_aw2_control_switch_capture_put(struct snd_kcontrol *kcontrol,
					      struct snd_ctl_elem_value
					      *ucontrol)
{
	struct aw2 *chip = snd_kcontrol_chip(kcontrol);
	int changed = 0;
	int is_disgital =
	    snd_aw2_saa7146_is_using_digital_input(&chip->saa7146);

	if (((ucontrol->value.integer.value[0] == CTL_ROUTE_DIGITAL)
	     && !is_disgital)
	    || ((ucontrol->value.integer.value[0] == CTL_ROUTE_ANALOG)
		&& is_disgital)) {
		snd_aw2_saa7146_use_digital_input(&chip->saa7146, !is_disgital);
		changed = 1;
	}
	return changed;
}
