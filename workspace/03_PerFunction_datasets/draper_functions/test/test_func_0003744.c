ringbuf_copy(Ringbuf *rb){
	Ringbuf *out;
	out = ringbuf_init(&out, rb->fill+1);
	int i;
	uint64_t offset = rb->read;
	for(i = rb->read; i != rb->write; i=(i+1)%(rb->num_keys)){
		out->keys[i-offset] = rb->keys[i];
		rb->keys[i] = NULL;
	}
	out->read = 0;
	out->write = rb->fill;
	out->fill = rb->fill;
	rb->write = 0;
	rb->read = 0;
	rb->fill = 0;
	return out;
}
