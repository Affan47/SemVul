dc_fread(void *ptr, size_t size, size_t items, FILE *fp)
{
	int	rc ;
	struct vsp_node *node;

	node = get_vsp_node(FILE_NO(fp));
	if( node == NULL ) {
		return system_fread( ptr, size, items, fp);
	}

	rc= dc_real_read(node,ptr,size*items) ;
	switch(rc) {
		case -1:
		case 0:
#if defined(__linux__) || defined(__GNU__) || defined(__FreeBSD_kernel__) || defined(__CYGWIN__)
			((FILE *)fp)->_flags |= _IO_EOF_SEEN;
#else
			((FILE *)fp)->_flag |= _IOEOF;
#endif
			rc = 0;
			break ;
		default:
			rc= (rc+size-1)/size ;
			break ;
	}

	m_unlock(&node->mux);
	return rc ;
}
