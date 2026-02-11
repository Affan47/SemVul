tms5220_reset(void)
{


	fifo_head = fifo_tail = fifo_count = fifo_bits_taken = 0;


	tms5220_speaking = speak_external = talk_status = first_frame = last_frame = irq_pin = 0;
#if USE_OBSOLETE_HACK
	speak_delay_frames = 0;
#endif
	if (irq_func) irq_func(0);
	buffer_empty = buffer_low = 1;

	RDB_flag = FALSE;


	old_energy = new_energy = current_energy = target_energy = 0;
	old_pitch = new_pitch = current_pitch = target_pitch = 0;
	memset(old_k, 0, sizeof(old_k));
	memset(new_k, 0, sizeof(new_k));
	memset(current_k, 0, sizeof(current_k));
	memset(target_k, 0, sizeof(target_k));


	interp_count = sample_count = pitch_count = 0;
	randbit = 0;
	memset(u, 0, sizeof(u));
	memset(x, 0, sizeof(x));

	if (load_address_callback)
		(*load_address_callback)(0);

	schedule_dummy_read = TRUE;
}
