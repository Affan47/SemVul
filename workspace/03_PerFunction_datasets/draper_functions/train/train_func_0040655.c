itemcmp(const char *patt, const char *item)
{


	if (!strcmp(patt, "*"))
		return 0;
        return item ? g_strcasecmp(patt, item) : 1;
}
