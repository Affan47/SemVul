snd_emu1010_output_source_put(struct snd_kcontrol *kcontrol,
                                 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	unsigned int channel;

	val = ucontrol->value.enumerated.item[0];
	if (val >= 53 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     val >= 49))
		return -EINVAL;
	channel = (kcontrol->private_value) & 0xff;

	if (channel >= 24 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     channel >= 18))
		return -EINVAL;
	if (emu->emu1010.output_source[channel] == val)
		return 0;
	emu->emu1010.output_source[channel] = val;
	if (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616)
		snd_emu1010_fpga_link_dst_src_write(emu,
			emu1616_output_dst[channel], emu1616_src_regs[val]);
	else
		snd_emu1010_fpga_link_dst_src_write(emu,
			emu1010_output_dst[channel], emu1010_src_regs[val]);
	return 1;
}
