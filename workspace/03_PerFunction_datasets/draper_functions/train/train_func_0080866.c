dump_job_step_state(struct job_record *job_ptr,
				struct step_record *step_ptr, Buf buffer)
{
	pack32(step_ptr->step_id, buffer);
	pack16(step_ptr->cyclic_alloc, buffer);
	pack16(step_ptr->port, buffer);
	pack16(step_ptr->ckpt_interval, buffer);
	pack16(step_ptr->cpus_per_task, buffer);
	pack16(step_ptr->resv_port_cnt, buffer);

	pack8(step_ptr->no_kill, buffer);

	pack32(step_ptr->cpu_count, buffer);
	pack32(step_ptr->mem_per_cpu, buffer);
	pack32(step_ptr->exit_code, buffer);
	if (step_ptr->exit_code != NO_VAL) {
		pack_bit_fmt(step_ptr->exit_node_bitmap, buffer);
		pack16((uint16_t) _bitstr_bits(step_ptr->exit_node_bitmap),
			buffer);
	}
	if (step_ptr->core_bitmap_job) {
		uint32_t core_size = bit_size(step_ptr->core_bitmap_job);
		pack32(core_size, buffer);
		pack_bit_fmt(step_ptr->core_bitmap_job, buffer);
	} else
		pack32((uint32_t) 0, buffer);

	pack32(step_ptr->time_limit, buffer);
	pack_time(step_ptr->start_time, buffer);
	pack_time(step_ptr->pre_sus_time, buffer);
	pack_time(step_ptr->tot_sus_time, buffer);
	pack_time(step_ptr->ckpt_time, buffer);

	packstr(step_ptr->host,  buffer);
	packstr(step_ptr->resv_ports, buffer);
	packstr(step_ptr->name, buffer);
	packstr(step_ptr->network, buffer);
	packstr(step_ptr->ckpt_dir, buffer);

	packstr(step_ptr->gres, buffer);
	(void) gres_plugin_step_state_pack(step_ptr->gres_list, buffer,
					   job_ptr->job_id, step_ptr->step_id,
					   SLURM_PROTOCOL_VERSION);

	pack16(step_ptr->batch_step, buffer);
	if (!step_ptr->batch_step) {
		pack_slurm_step_layout(step_ptr->step_layout, buffer,
				       SLURM_PROTOCOL_VERSION);
		switch_pack_jobinfo(step_ptr->switch_job, buffer);
	}
	checkpoint_pack_jobinfo(step_ptr->check_job, buffer,
				SLURM_PROTOCOL_VERSION);
	select_g_select_jobinfo_pack(step_ptr->select_jobinfo, buffer,
				     SLURM_PROTOCOL_VERSION);

}
