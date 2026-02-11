lookup_value_check(const nlookup_t *nl)
{
	lookup_check(nl);
	g_assert(lookup_is_fetching(nl));
}
