pcmidi_set_operational(struct pcmidi_snd *pm)
{
	if (pm->ifnum != 1)
		return 0;

	pcmidi_get_output_report(pm);
	pcmidi_submit_output_report(pm, 0xc1);
	return 0;
}
