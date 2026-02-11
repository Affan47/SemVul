cg_equal (GOColorGroup const *a, GOColorGroup const *b)
{
	if (a == b)
		return TRUE;
	if (a->context != b->context)
		return FALSE;
	return g_str_equal (a->name, b->name);
}
