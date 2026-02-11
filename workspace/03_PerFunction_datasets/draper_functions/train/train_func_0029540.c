rb_econv_memsize(rb_econv_t *ec)
{
    size_t size = sizeof(rb_econv_t);
    int i;

    if (ec->replacement_allocated) {
	size += ec->replacement_len;
    }
    for (i = 0; i < ec->num_trans; i++) {
	size += rb_transcoding_memsize(ec->elems[i].tc);

	if (ec->elems[i].out_buf_start) {
            size += ec->elems[i].out_buf_end - ec->elems[i].out_buf_start;
	}
    }
    size += ec->in_buf_end - ec->in_buf_start;
    size += sizeof(rb_econv_elem_t) * ec->num_allocated;

    return size;
}
