_dump_part_state(struct part_record *part_ptr, Buf buffer)
{
	xassert(part_ptr);
	if (default_part_loc == part_ptr)
		part_ptr->flags |= PART_FLAG_DEFAULT;
	else
		part_ptr->flags &= (~PART_FLAG_DEFAULT);

	packstr(part_ptr->name,          buffer);
	pack32(part_ptr->grace_time,	 buffer);
	pack32(part_ptr->max_time,       buffer);
	pack32(part_ptr->default_time,   buffer);
	pack32(part_ptr->max_cpus_per_node, buffer);
	pack32(part_ptr->max_nodes_orig, buffer);
	pack32(part_ptr->min_nodes_orig, buffer);

	pack16(part_ptr->flags,          buffer);
	pack16(part_ptr->max_share,      buffer);
	pack16(part_ptr->preempt_mode,   buffer);
	pack16(part_ptr->priority,       buffer);

	pack16(part_ptr->state_up,       buffer);
	pack16(part_ptr->cr_type,        buffer);

	packstr(part_ptr->allow_accounts, buffer);
	packstr(part_ptr->allow_groups,  buffer);
	packstr(part_ptr->allow_qos,     buffer);
	packstr(part_ptr->allow_alloc_nodes, buffer);
	packstr(part_ptr->alternate,     buffer);
	packstr(part_ptr->deny_accounts, buffer);
	packstr(part_ptr->deny_qos,      buffer);
	packstr(part_ptr->nodes,         buffer);
}
