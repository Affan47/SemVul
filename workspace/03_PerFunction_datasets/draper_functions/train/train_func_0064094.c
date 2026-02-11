qt_fill_input_buffer(j_decompress_ptr cinfo)
{
    int num_read;
    my_jpeg_source_mgr* src = (my_jpeg_source_mgr*)cinfo->src;
    src->next_input_byte = src->buffer;
    num_read = fread( (char*)src->buffer, 1, max_buf, src->f );

    if ( num_read <= 0 ) {

	src->buffer[0] = (JOCTET) 0xFF;
	src->buffer[1] = (JOCTET) JPEG_EOI;
	src->bytes_in_buffer = 2;
    } else {
	src->bytes_in_buffer = num_read;
    }
#if defined(Q_OS_UNIXWARE)
    return B_TRUE;
#else
    return TRUE;
#endif
}
