uri_text_decode(gchar *text)
{
	if (strchr(text, '%'))
		{
		gchar *w;
		gchar *r;

		w = r = text;

		while (*r != '\0')
			{
			if (*r == '%' && *(r + 1) != '\0' && *(r + 2) != '\0')
				{
				gchar t[3];
				gint n;

				r++;
				t[0] = *r;
				r++;
				t[1] = *r;
				t[2] = '\0';
				n = (gint)strtol(t, NULL, 16);
				if (n > 0 && n < 256)
					{
					*w = (gchar)n;
					}
				else
					{

					r -= 2;
					*w = *r;
					}
				}
			else if (w != r)
				{
				*w = *r;
				}
			r++;
			w++;
			}
		if (*w != '\0') *w = '\0';
		}
}
