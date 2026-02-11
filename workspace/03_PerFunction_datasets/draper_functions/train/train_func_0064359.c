razf_write(RAZF* rz, const void *data, size_t size){
	size_t ori_size;
	int n;
	int64_t next_block;
	ori_size = size;
	next_block = ((rz->in / RZ_BLOCK_SIZE) + 1) * RZ_BLOCK_SIZE;
	while(rz->in + rz->buf_len + size >= next_block){
		n = next_block - rz->in - rz->buf_len;
		_razf_buffered_write(rz, data, n);
		data += n;
		size -= n;
		razf_flush(rz);
		add_zindex(rz, rz->in, rz->out);
		next_block = ((rz->in / RZ_BLOCK_SIZE) + 1) * RZ_BLOCK_SIZE;
	}
	_razf_buffered_write(rz, data, size);
	return ori_size;
}
