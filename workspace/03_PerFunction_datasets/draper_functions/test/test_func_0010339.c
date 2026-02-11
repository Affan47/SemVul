_map_scb (struct snd_cs46xx *chip, char * name, u32 dest)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * desc = NULL;
	int index;

	if (ins->nscb == DSP_MAX_SCB_DESC - 1) {
		dev_err(chip->card->dev,
			"dsp_spos: got no place for other SCB\n");
		return NULL;
	}

	index = find_free_scb_index (ins);

	memset(&ins->scbs[index], 0, sizeof(ins->scbs[index]));
	strcpy(ins->scbs[index].scb_name, name);
	ins->scbs[index].address = dest;
	ins->scbs[index].index = index;
	ins->scbs[index].ref_count = 1;

	desc = (ins->scbs + index);
	ins->scbs[index].scb_symbol = add_symbol (chip, name, dest, SYMBOL_PARAMETER);

	if (index > ins->scb_highest_frag_index)
		ins->scb_highest_frag_index = index;

	if (index == ins->nscb)
		ins->nscb++;

	return desc;
}
