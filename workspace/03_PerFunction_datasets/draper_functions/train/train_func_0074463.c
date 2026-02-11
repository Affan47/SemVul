buffer_manager_read_key(buffer_manager_t * buffer_manager, cmph_uint32 index, cmph_uint32 * keylen)
{
	cmph_uint8 * key = NULL;
	if (buffer_manager->pos_avail_list >= 0 )
	{
		cmph_uint32 new_capacity = buffer_entry_get_capacity(buffer_manager->buffer_entries[index]) + buffer_manager->memory_avail_list[(buffer_manager->pos_avail_list)--];
		buffer_entry_set_capacity(buffer_manager->buffer_entries[index], new_capacity);
	}
	key = buffer_entry_read_key(buffer_manager->buffer_entries[index], keylen);
	if (key == NULL)
	{
		buffer_manager->memory_avail_list[++(buffer_manager->pos_avail_list)] = buffer_entry_get_capacity(buffer_manager->buffer_entries[index]);
	}
	return key;
}
