snd_pcm_mulaw_dump(snd_pcm_t *pcm, snd_output_t *out)
{
	snd_pcm_mulaw_t *mulaw = pcm->private_data;
	snd_output_printf(out, "Mu-Law conversion PCM (%s)\n",
		snd_pcm_format_name(mulaw->sformat));
	if (pcm->setup) {
		snd_output_printf(out, "Its setup is:\n");
		snd_pcm_dump_setup(pcm, out);
	}
	snd_output_printf(out, "Slave: ");
	snd_pcm_dump(mulaw->plug.gen.slave, out);
}
