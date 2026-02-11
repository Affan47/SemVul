lmo_lookup(lmo_archive_t *ar, const char *key, char *dest, int len)
{
	uint32_t look_key = sfh_hash(key, strlen(key));
	int copy_len = -1;
	lmo_entry_t *entry;

	if( !ar )
		return copy_len;

	entry = ar->index;

	while( entry != NULL )
	{
		if( entry->key_id == look_key )
		{
			copy_len = ((len - 1) > entry->length) ? entry->length : (len - 1);
			memcpy(dest, &ar->mmap[entry->offset], copy_len);
			dest[copy_len] = '\0';

			break;
		}

		entry = entry->next;
	}

	return copy_len;
}
