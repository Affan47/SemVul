mi_fmt_init( unsigned int size )
{
	mi_fmt_buf = (char*)pkg_malloc(size);
	if (mi_fmt_buf==NULL) {
		LM_ERR("no more pkg mem\n");
		return -1;
	}
	mi_fmt_buf_len = size;
	return 0;
}
