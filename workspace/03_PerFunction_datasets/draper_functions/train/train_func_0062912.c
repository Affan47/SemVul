custom_header_get_str(CustomHeader *ch)
{
	return g_strdup_printf("%i:%s: %s",
			       ch->account_id, ch->name,
			       ch->value ? ch->value : "");
}
