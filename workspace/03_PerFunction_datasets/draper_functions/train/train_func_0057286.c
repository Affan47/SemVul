rhash_init(unsigned hash_id)
{
	unsigned tail_bit_index;
	unsigned num = 0;
	rhash_context *rctx = NULL;
	size_t hash_size_sum = 0;

	unsigned i, bit_index, id;
	struct rhash_hash_info* info;
	size_t aligned_size;
	char* phash_ctx;

	hash_id &= RHASH_ALL_HASHES;
	if(hash_id == 0) return NULL;

	tail_bit_index = rhash_ctz(hash_id);
	assert(tail_bit_index < RHASH_HASH_COUNT);

	id = 1 << tail_bit_index;

	if(hash_id == id) {

		num = 1;
		info = &rhash_info_table[tail_bit_index];
		hash_size_sum = info->context_size;
	} else {

		for(bit_index = tail_bit_index; id <= hash_id; bit_index++, id = id << 1) {
			assert(id != 0);
			assert(bit_index < RHASH_HASH_COUNT);
			info = &rhash_info_table[bit_index];
			if(hash_id & id) {

				aligned_size = (info->context_size + 7) & ~7;
				hash_size_sum += aligned_size;
				num++;
			}
		}
		assert(num > 1);
	}


	aligned_size = (offsetof(rhash_context, vector[num]) + 7) & ~7;
	assert(aligned_size >= sizeof(rhash_context));


	rctx = (rhash_context*)rsh_malloc(aligned_size + hash_size_sum);


	rctx->msg_size = 0;
	rctx->hash_id = hash_id;
	rctx->state = STATE_ACTIVE;
	rctx->hash_vector_size = num;
	rctx->callback = rctx->callback_data = NULL;


	phash_ctx = (char*)rctx + aligned_size;
	assert(phash_ctx >= (char*)&rctx->vector[num]);


	for(bit_index = tail_bit_index, id = 1 << tail_bit_index, i = 0;
		id <= hash_id; bit_index++, id = id << 1)
	{

		if((hash_id & id) != 0) {
			info = &rhash_info_table[bit_index];
			assert(info->context_size > 0);
			assert(((phash_ctx - (char*)0) & 7) == 0);
			assert(info->init != NULL);

			rctx->vector[i].hash_info = info;
			rctx->vector[i].context = phash_ctx;


			if((id & RHASH_BTIH) != 0) rctx->bt_ctx = phash_ctx;
			phash_ctx += (info->context_size + 7) & ~7;


			info->init(rctx->vector[i].context);
			i++;
		}
	}

	return rctx;
}
