_dsp_unlink_scb (struct snd_cs46xx *chip, struct dsp_scb_descriptor * scb)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if ( scb->parent_scb_ptr ) {

		if (snd_BUG_ON(scb->parent_scb_ptr->sub_list_ptr != scb &&
			       scb->parent_scb_ptr->next_scb_ptr != scb))
			return;

		if (scb->parent_scb_ptr->sub_list_ptr == scb) {

			if (scb->next_scb_ptr == ins->the_null_scb) {

				scb->parent_scb_ptr->sub_list_ptr = scb->sub_list_ptr;

				if (scb->sub_list_ptr != ins->the_null_scb) {
					scb->sub_list_ptr->parent_scb_ptr = scb->parent_scb_ptr;
				}
				scb->sub_list_ptr = ins->the_null_scb;
			} else {

				scb->parent_scb_ptr->sub_list_ptr = scb->next_scb_ptr;

				if (scb->next_scb_ptr != ins->the_null_scb) {

					scb->next_scb_ptr->parent_scb_ptr = scb->parent_scb_ptr;
				}
				scb->next_scb_ptr = ins->the_null_scb;
			}
		} else {
			scb->parent_scb_ptr->next_scb_ptr = scb->next_scb_ptr;

			if (scb->next_scb_ptr != ins->the_null_scb) {

				scb->next_scb_ptr->parent_scb_ptr = scb->parent_scb_ptr;
			}
			scb->next_scb_ptr = ins->the_null_scb;
		}


		cs46xx_dsp_spos_update_scb(chip,scb->parent_scb_ptr);


		cs46xx_dsp_spos_update_scb(chip,scb);

		scb->parent_scb_ptr = NULL;
	}
}
