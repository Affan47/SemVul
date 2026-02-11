cs46xx_dsp_proc_task_tree_read (struct snd_info_entry *entry,
					    struct snd_info_buffer *buffer)
{
	struct snd_cs46xx *chip = entry->private_data;
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	int i, j, col;
	void __iomem *dst = chip->region.idx[1].remap_addr + DSP_PARAMETER_BYTE_OFFSET;

	mutex_lock(&chip->spos_mutex);
	snd_iprintf(buffer, "TASK TREES:\n");
	for ( i = 0; i < ins->ntask; ++i) {
		snd_iprintf(buffer,"\n%04x %s:\n",ins->tasks[i].address,ins->tasks[i].task_name);

		for (col = 0,j = 0;j < ins->tasks[i].size; j++,col++) {
			u32 val;
			if (col == 4) {
				snd_iprintf(buffer,"\n");
				col = 0;
			}
			val = readl(dst + (ins->tasks[i].address + j) * sizeof(u32));
			snd_iprintf(buffer,"%08x ",val);
		}
	}

	snd_iprintf(buffer,"\n");
	mutex_unlock(&chip->spos_mutex);
}
