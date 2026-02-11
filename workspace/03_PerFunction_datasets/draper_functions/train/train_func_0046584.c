get_fat_entry (fat_chain * chain, unsigned int i_sect)
{

    if (!chain)
	return NULL;
    if (i_sect < chain->fat_array_count)
	return *(chain->fat_array + i_sect);
    return NULL;
}
