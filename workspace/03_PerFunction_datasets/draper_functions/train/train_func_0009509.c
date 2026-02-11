pgp_locate_armor_header(gchar *textdata, const gchar *armor_header)
{
	gchar *pos;

	pos = strstr(textdata, armor_header);


	if (pos != NULL && (pos == textdata || *(pos-1) == '\n'))
	{
	      return pos;
	}
	return NULL;
}
