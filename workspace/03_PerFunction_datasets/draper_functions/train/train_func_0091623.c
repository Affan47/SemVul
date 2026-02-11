msgpack_unpacker_execute(msgpack_unpacker* mpac)
{
	size_t off = mpac->off;
	int ret = template_execute(CTX_CAST(mpac->ctx),
			mpac->buffer, mpac->used, &mpac->off);
	if(mpac->off > off) {
		mpac->parsed += mpac->off - off;
	}
	return ret;
}
