_nodes_in_sets(bitstr_t *req_bitmap,
			  struct node_set * node_set_ptr,
			  int node_set_size)
{
	bitstr_t *scratch_bitmap = NULL;
	int error_code = SLURM_SUCCESS, i;

	for (i=0; i<node_set_size; i++) {
		if (scratch_bitmap)
			bit_or(scratch_bitmap,
			       node_set_ptr[i].my_bitmap);
		else {
			scratch_bitmap =
			    bit_copy(node_set_ptr[i].my_bitmap);
			if (scratch_bitmap == NULL)
				fatal("bit_copy malloc failure");
		}
	}

	if ((scratch_bitmap == NULL)
	    || (bit_super_set(req_bitmap, scratch_bitmap) != 1))
		error_code = ESLURM_REQUESTED_NODE_CONFIG_UNAVAILABLE;

	FREE_NULL_BITMAP(scratch_bitmap);
	return error_code;
}
