select_p_select_nodeinfo_unpack(select_nodeinfo_t **nodeinfo,
					   Buf buffer,
					   uint16_t protocol_version)
{
	select_nodeinfo_t *nodeinfo_ptr = NULL;

	nodeinfo_ptr = select_p_select_nodeinfo_alloc();
	*nodeinfo = nodeinfo_ptr;

	safe_unpack16(&nodeinfo_ptr->alloc_cpus, buffer);

	return SLURM_SUCCESS;

unpack_error:
	error("select_nodeinfo_unpack: error unpacking here");
	select_p_select_nodeinfo_free(nodeinfo_ptr);
	*nodeinfo = NULL;

	return SLURM_ERROR;
}
