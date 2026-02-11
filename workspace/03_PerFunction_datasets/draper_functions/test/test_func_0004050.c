pss_coproc_reset(void *dev_info)
{
	if (pss_synthLen)
		if (!pss_download_boot(devc, pss_synth, pss_synthLen, CPF_FIRST | CPF_LAST))
		{
			printk(KERN_ERR "PSS: Unable to load MIDI synth microcode to DSP.\n");
		}
	nonstandard_microcode = 0;
}
