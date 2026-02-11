dc_ftello64(FILE *fp)
{

	off64_t rc;
	struct vsp_node *node;

	node = get_vsp_node(FILE_NO(fp));

	if( node == NULL ) {
		return system_ftello64(fp);
	}


	if (fp == NULL) {
		return -1;
	}

 	rc = dc_real_lseek( node, (off64_t)0, SEEK_CUR);
	m_unlock(&node->mux);


	return rc;
}
