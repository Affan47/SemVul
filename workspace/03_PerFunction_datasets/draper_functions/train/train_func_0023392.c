go_pattern_get_pattern (GOPattern const *pat)
{
	g_return_val_if_fail (pat != NULL && pat->pattern < GO_PATTERN_MAX, NULL);
	return go_patterns [pat->pattern].pattern;
}
