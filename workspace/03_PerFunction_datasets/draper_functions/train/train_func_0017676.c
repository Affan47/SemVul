gfire_bitlist_set(gfire_bitlist *p_list, guint32 p_index, gboolean p_isset)
{
	if(!p_list)
		return;

	if((p_index >> 3) >= p_list->size)
	{
		guint32 oldsize = p_list->size;
		p_list->size = (p_index >> 3) + 10;
		p_list->data = g_realloc(p_list->data, p_list->size);
		memset(p_list->data + oldsize, 0, p_list->size - oldsize);
	}

	if(p_isset)
	{
		if(!(*(p_list->data + (p_index >> 3)) & (1 << (p_index & 7))))
			p_list->bits_set++;

		*(p_list->data + (p_index >> 3)) |= (1 << (p_index & 7));
	}
	else
	{
		if(*(p_list->data + (p_index >> 3)) & (1 << (p_index & 7)))
		{
			p_list->bits_set--;
			*(p_list->data + (p_index >> 3)) &= ~(1 << (p_index & 7));
		}
	}
}
