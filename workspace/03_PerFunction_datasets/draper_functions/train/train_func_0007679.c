_part_access_check(struct part_record *part_ptr,
			      job_desc_msg_t * job_desc, bitstr_t *req_bitmap,
			      uid_t submit_uid)
{
	uint32_t total_nodes;


	if ((part_ptr->flags & PART_FLAG_REQ_RESV) &&
	    (!job_desc->reservation || !strlen(job_desc->reservation))) {
		info("_part_access_check: uid %u access to partition %s "
		     "denied, requires reservation",
		     (unsigned int) submit_uid, part_ptr->name);
		return ESLURM_ACCESS_DENIED;
	}

	if ((part_ptr->flags & PART_FLAG_ROOT_ONLY) && (submit_uid != 0) &&
	    (submit_uid != slurmctld_conf.slurm_user_id)) {
		info("_part_access_check: uid %u access to partition %s "
		     "denied, not root",
		     (unsigned int) submit_uid, part_ptr->name);
		return ESLURM_ACCESS_DENIED;
	}

	if ((job_desc->user_id == 0) && (part_ptr->flags & PART_FLAG_NO_ROOT)) {
		error("_part_access_check: Security violation, SUBMIT_JOB for "
		      "user root disabled");
		return ESLURM_USER_ID_MISSING;
	}

	if (validate_group(part_ptr, job_desc->user_id) == 0) {
		info("_part_access_check: uid %u access to partition %s "
		     "denied, bad group",
		     (unsigned int) job_desc->user_id, part_ptr->name);
		return ESLURM_JOB_MISSING_REQUIRED_PARTITION_GROUP;
	}

	if (validate_alloc_node(part_ptr, job_desc->alloc_node) == 0) {
		info("_part_access_check: uid %u access to partition %s "
		     "denied, bad allocating node: %s",
		     (unsigned int) job_desc->user_id, part_ptr->name,
		     job_desc->alloc_node);
		return ESLURM_ACCESS_DENIED;
	}

	if ((part_ptr->state_up & PARTITION_SCHED) &&
	    (job_desc->min_cpus != NO_VAL) &&
	    (job_desc->min_cpus >  part_ptr->total_cpus)) {
		info("_part_access_check: Job requested too many cpus (%u) of "
		     "partition %s(%u)",
		     job_desc->min_cpus, part_ptr->name,
		     part_ptr->total_cpus);
		return ESLURM_TOO_MANY_REQUESTED_CPUS;
	}

	total_nodes = part_ptr->total_nodes;
	select_g_alter_node_cnt(SELECT_APPLY_NODE_MAX_OFFSET, &total_nodes);
	if ((part_ptr->state_up & PARTITION_SCHED) &&
	    (job_desc->min_nodes != NO_VAL) &&
	    (job_desc->min_nodes > total_nodes)) {
		info("_part_access_check: Job requested too many nodes (%u) "
		     "of partition %s(%u)",
		     job_desc->min_nodes, part_ptr->name, total_nodes);
		return ESLURM_INVALID_NODE_COUNT;
	}

	if (req_bitmap && !bit_super_set(req_bitmap, part_ptr->node_bitmap)) {
		info("_part_access_check: requested nodes %s not in "
		     "partition %s", job_desc->req_nodes, part_ptr->name);
		return ESLURM_REQUESTED_NODES_NOT_IN_PARTITION;
	}

	return SLURM_SUCCESS;
}
