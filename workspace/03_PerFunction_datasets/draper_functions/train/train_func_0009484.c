dc_fseeko64(FILE *fp, off64_t offset, int whence)
{

	off64_t rc;
	struct vsp_node *node;

	node = get_vsp_node(FILE_NO(fp));
	if( node == NULL ) {
		return system_fseeko64( fp, offset, whence);
	}


	if (fp == NULL) {
		return -1;
	}

 	rc = dc_real_lseek(node,offset,whence);
	m_unlock(&node->mux);

	return rc < 0 ? -1 : 0;
}
