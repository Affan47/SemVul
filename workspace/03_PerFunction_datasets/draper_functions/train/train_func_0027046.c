_unpack_epilog_comp_msg(epilog_complete_msg_t ** msg, Buf buffer,
			uint16_t protocol_version)
{
	epilog_complete_msg_t *tmp_ptr;
	uint32_t uint32_tmp;


	xassert(msg);
	tmp_ptr = xmalloc(sizeof(epilog_complete_msg_t));
	*msg = tmp_ptr;

	safe_unpack32(&(tmp_ptr->job_id), buffer);
	safe_unpack32(&(tmp_ptr->return_code), buffer);
	safe_unpackstr_xmalloc(& (tmp_ptr->node_name), &uint32_tmp, buffer);
	if (switch_g_alloc_node_info(&tmp_ptr->switch_nodeinfo)
	    ||  switch_g_unpack_node_info(tmp_ptr->switch_nodeinfo, buffer))
		goto unpack_error;

	return SLURM_SUCCESS;

unpack_error:
	slurm_free_epilog_complete_msg(tmp_ptr);
	*msg = NULL;
	return SLURM_ERROR;
}
