snd_ak4114_proc_regs_read(struct snd_info_entry *entry,
		struct snd_info_buffer *buffer)
{
	struct ak4114 *ak4114 = entry->private_data;
	int reg, val;

	for (reg = 0; reg < 0x20; reg++) {
		val = reg_read(ak4114, reg);
		snd_iprintf(buffer, "0x%02x = 0x%02x\n", reg, val);
	}
}
