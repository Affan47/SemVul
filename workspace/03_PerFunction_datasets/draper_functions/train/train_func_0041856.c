_dsp_create_generic_scb (struct snd_cs46xx *chip, char * name, u32 * scb_data, u32 dest,
                         struct dsp_symbol_entry * task_entry,
                         struct dsp_scb_descriptor * parent_scb,
                         int scb_child_type)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * scb;

	unsigned long flags;

	if (snd_BUG_ON(!ins->the_null_scb))
		return NULL;


	scb_data[SCBsubListPtr] =
		(ins->the_null_scb->address << 0x10) | ins->the_null_scb->address;

	scb_data[SCBfuncEntryPtr] &= 0xFFFF0000;
	scb_data[SCBfuncEntryPtr] |= task_entry->address;

	dev_dbg(chip->card->dev, "dsp_spos: creating SCB <%s>\n", name);

	scb = cs46xx_dsp_create_scb(chip,name,scb_data,dest);


	scb->sub_list_ptr = ins->the_null_scb;
	scb->next_scb_ptr = ins->the_null_scb;

	scb->parent_scb_ptr = parent_scb;
	scb->task_entry = task_entry;


	if (scb->parent_scb_ptr) {
#if 0
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr = %s\n",
			scb->parent_scb_ptr->scb_name);
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr->next_scb_ptr = %s\n",
			scb->parent_scb_ptr->next_scb_ptr->scb_name);
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr->sub_list_ptr = %s\n",
			scb->parent_scb_ptr->sub_list_ptr->scb_name);
#endif

		if (scb_child_type == SCB_ON_PARENT_NEXT_SCB) {
			if (snd_BUG_ON(scb->parent_scb_ptr->next_scb_ptr !=
				       ins->the_null_scb))
				return NULL;

			scb->parent_scb_ptr->next_scb_ptr = scb;

		} else if (scb_child_type == SCB_ON_PARENT_SUBLIST_SCB) {
			if (snd_BUG_ON(scb->parent_scb_ptr->sub_list_ptr !=
				       ins->the_null_scb))
				return NULL;

			scb->parent_scb_ptr->sub_list_ptr = scb;
		} else {
			snd_BUG();
		}

		spin_lock_irqsave(&chip->reg_lock, flags);


		cs46xx_dsp_spos_update_scb(chip,scb->parent_scb_ptr);

		spin_unlock_irqrestore(&chip->reg_lock, flags);
	}


	cs46xx_dsp_proc_register_scb_desc (chip,scb);

	return scb;
}
