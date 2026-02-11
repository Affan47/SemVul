FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair(FLAC__StreamMetadata_VorbisComment_Entry *entry, const char *field_name, const char *field_value)
{
	FLAC__ASSERT(0 != entry);
	FLAC__ASSERT(0 != field_name);
	FLAC__ASSERT(0 != field_value);

	if(!FLAC__format_vorbiscomment_entry_name_is_legal(field_name))
		return false;
	if(!FLAC__format_vorbiscomment_entry_value_is_legal((const FLAC__byte *)field_value, (unsigned)(-1)))
		return false;

	{
		const size_t nn = strlen(field_name);
		const size_t nv = strlen(field_value);
		entry->length = nn + 1  + nv;
		if(0 == (entry->entry = safe_malloc_add_4op_(nn, 1, nv, 1)))
			return false;
		memcpy(entry->entry, field_name, nn);
		entry->entry[nn] = '=';
		memcpy(entry->entry+nn+1, field_value, nv);
		entry->entry[entry->length] = '\0';
	}

	return true;
}
