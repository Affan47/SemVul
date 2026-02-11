fluid_sequencer_set_time_scale (fluid_sequencer_t* seq, double scale)
{
	if (scale <= 0) {
		fluid_log(FLUID_WARN, "sequencer: scale <= 0 : %f\n", scale);
		return;
	}

	if (scale > 1000.0)

		scale = 1000.0;

	if (seq->scale != scale) {
		double oldScale = seq->scale;


		if (seq->timer) {
			delete_fluid_timer(seq->timer);
			seq->timer = NULL;
		}

		seq->scale = scale;


		seq->queue0StartTime =  (seq->queue0StartTime + seq->prevCellNb)*(seq->scale/oldScale) - seq->prevCellNb;


		{
			fluid_evt_entry* tmp;
			tmp = seq->preQueue;
			while (tmp) {
				if (tmp->entryType == FLUID_EVT_ENTRY_INSERT)
					tmp->evt.time = tmp->evt.time*seq->scale/oldScale;

				tmp = tmp->next;
			}
		}


		if (seq->useSystemTimer) {
			seq->timer = new_fluid_timer((int)(1000/seq->scale), _fluid_seq_queue_process, (void *)seq, TRUE, FALSE, TRUE);
		}
	}
}
