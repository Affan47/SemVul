rhash_update(rhash ctx, const void* message, size_t length)
{
	rhash_context_ext* const ectx = (rhash_context_ext*)ctx;
	unsigned i;

	assert(ectx->hash_vector_size <= RHASH_HASH_COUNT);
	if(ectx->state != STATE_ACTIVE) return 0;

	ctx->msg_size += length;


	for(i = 0; i < ectx->hash_vector_size; i++) {
		struct rhash_hash_info* info = ectx->vector[i].hash_info;
		assert(info->update != 0);
		info->update(ectx->vector[i].context, message, length);
	}
	return 0;
}
