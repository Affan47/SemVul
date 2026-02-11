print_header(FILE *f, char *template, const char *me,
			 const char *from_time, const char *from_mta)
{
        unsigned char c, c2;
        int i = 0;

        while ((c=template[i++]) > 0)
	{
		char        kw[64];
		if (c != '[')
		{
			putc(c, f);
                        continue;
		}

		if (template[i] != '#')
		{
			putc('[', f);
			continue;
		}

		++i;

		c2=0;
		while ((c=template[i]) != 0 && (isalnum(c) || c == '_'))
		{
                        if (c2 < sizeof(kw)-1)
                                kw[c2++]=c;
			++i;
		}
		kw[c2]=0;

		if (c != '#')
		{
			fprintf(f, "[#%s", kw);
			continue;
		}

		++i;
		if (template[i] != ']')
		{
			fprintf(f, "[#%s#", kw);
			continue;
		}
		++i;
		if (strcmp(kw, "ME") == 0)
		{
			fprintf(f, "%s", me);
		}
		else if (strcmp(kw, "FROMTIME") == 0)
		{
			fprintf(f, "%s", from_time);
		}
		else if (strcmp(kw, "FROMMTA") == 0)
		{
			fprintf(f, "%s", from_mta);
		}
        }
}
