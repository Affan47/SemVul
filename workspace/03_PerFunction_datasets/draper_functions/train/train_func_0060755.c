_razf_write(RAZF* rz, const void *data, int size){
	int tout;
	rz->stream->avail_in = size;
	rz->stream->next_in  = (void*)data;
	while(1){
		tout = rz->stream->avail_out;
		deflate(rz->stream, Z_NO_FLUSH);
		rz->out += tout - rz->stream->avail_out;
		if(rz->stream->avail_out) break;
#ifdef _USE_KNETFILE
		write(rz->x.fpw, rz->outbuf, RZ_BUFFER_SIZE - rz->stream->avail_out);
#else
		write(rz->filedes, rz->outbuf, RZ_BUFFER_SIZE - rz->stream->avail_out);
#endif
		rz->stream->avail_out = RZ_BUFFER_SIZE;
		rz->stream->next_out  = rz->outbuf;
		if(rz->stream->avail_in == 0) break;
	};
	rz->in += size - rz->stream->avail_in;
	rz->block_off += size - rz->stream->avail_in;
}
