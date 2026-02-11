gpt_warning(char *dev)
{
	if (dev && gpt_probe_signature_devname(dev))
		fprintf(stderr, _("\nWARNING: GPT (GUID Partition Table) detected on '%s'! "
			"The util fdisk doesn't support GPT. Use GNU Parted.\n\n"), dev);
}
