asm_src_buffer_push(struct membuf *buffer)
{
    if(src_buffer_depth == MAX_SRC_BUFFER_DEPTH)
    {
	fprintf(stderr, "source buffers nested too deep\n");
	exit(-1);
    }
    src_buffers[src_buffer_depth++] = YY_CURRENT_BUFFER;
    yy_scan_bytes(membuf_get(buffer), membuf_memlen(buffer));
}
