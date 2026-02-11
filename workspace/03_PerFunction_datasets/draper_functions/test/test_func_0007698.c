midisynth_unsubscribe(void *private_data, struct snd_seq_port_subscribe *info)
{
	int err;
	struct seq_midisynth *msynth = private_data;

	if (snd_BUG_ON(!msynth->input_rfile.input))
		return -EINVAL;
	err = snd_rawmidi_kernel_release(&msynth->input_rfile);
	return err;
}
