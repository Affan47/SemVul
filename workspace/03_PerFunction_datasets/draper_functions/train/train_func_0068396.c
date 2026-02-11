shared_filter(shared_data_t *data,
						  shared_entry_t **in, shared_key_t **out,
						  void **unused1, id_match_t *me,
						  void **unused2, id_match_t *other)
{
	id_match_t my_match = ID_MATCH_NONE, other_match = ID_MATCH_NONE;
	shared_entry_t *entry = *in;

	if (data->type != SHARED_ANY &&
		entry->shared->get_type(entry->shared) != data->type)
	{
		return FALSE;
	}
	if (data->me)
	{
		my_match = has_owner(entry, data->me);
	}
	if (data->other)
	{
		other_match = has_owner(entry, data->other);
	}
	if ((data->me || data->other) && (!my_match && !other_match))
	{
		return FALSE;
	}
	*out = entry->shared;
	if (me)
	{
		*me = my_match;
	}
	if (other)
	{
		*other = other_match;
	}
	return TRUE;
}
