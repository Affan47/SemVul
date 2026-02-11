go_string_hash (gconstpointer gstr)
{
	return gstr ? ((GOStringImpl const *)gstr)->hash : 0;
}
