identifier_add (const char * string)
{
	int code = identifier_code++ ;
	if (!identifier_add_as (string, code)) return 0 ;
	return code ;
}
