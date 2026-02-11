chd_ph_mapping(cmph_config_t *mph, chd_ph_bucket_t * buckets, chd_ph_item_t * items, cmph_uint32 *max_bucket_size)
{
	register cmph_uint32 i = 0, g = 0;
	cmph_uint32 hl[3];
	chd_ph_config_data_t *chd_ph = (chd_ph_config_data_t *)mph->data;
	char * key = NULL;
	cmph_uint32 keylen = 0;
	chd_ph_map_item_t * map_item;
	chd_ph_map_item_t * map_items = malloc(chd_ph->m*sizeof(chd_ph_map_item_t));
	register cmph_uint32 mapping_iterations = 1000;
	*max_bucket_size = 0;
	while(1)
	{
		mapping_iterations--;
		if (chd_ph->hl) hash_state_destroy(chd_ph->hl);
		chd_ph->hl = hash_state_new(chd_ph->hashfunc, chd_ph->m);

		chd_ph_bucket_clean(buckets, chd_ph->nbuckets);

		mph->key_source->rewind(mph->key_source->data);

		for(i = 0; i < chd_ph->m; i++)
		{
			mph->key_source->read(mph->key_source->data, &key, &keylen);
			hash_vector(chd_ph->hl, key, keylen, hl);

			map_item = (map_items + i);

			g = hl[0] % chd_ph->nbuckets;
			map_item->f = hl[1] % chd_ph->n;
			map_item->h = hl[2] % (chd_ph->n - 1) + 1;
			map_item->bucket_num=g;
			mph->key_source->dispose(mph->key_source->data, key, keylen);


			buckets[g].size++;
			if(buckets[g].size > *max_bucket_size)
			{
				  *max_bucket_size = buckets[g].size;
			}
		}
		buckets[0].items_list = 0;
		for(i = 1; i < chd_ph->nbuckets; i++)
		{
			buckets[i].items_list = buckets[i-1].items_list + buckets[i - 1].size;
			buckets[i - 1].size = 0;
		};
		buckets[i - 1].size = 0;
		for(i = 0; i < chd_ph->m; i++)
		{
			map_item = (map_items + i);
			if(!chd_ph_bucket_insert(buckets, map_items, items, chd_ph->nbuckets, i))
				break;
		}
		if(i == chd_ph->m)
		{
			free(map_items);
			return 1;
		}

		if(mapping_iterations == 0)
		{
		      goto error;
		}
	}
error:
	free(map_items);
	hash_state_destroy(chd_ph->hl);
	chd_ph->hl = NULL;
	return 0;
}
