to_font_encoding(fz_context *ctx, pdf_font_desc *font, char *utf8)
{
	int i;
	int needs_converting = 0;


	for (i = 0; utf8[i] != '\0'; i++)
	{
		if (utf8[i] & 0x80)
			needs_converting = 1;
	}


	if (needs_converting && font->cid_to_ucs)
	{
		char *buf = fz_malloc(ctx, strlen(utf8) + 1);
		char *bufp = buf;

		fz_try(ctx)
		{
			while(*utf8)
			{
				if (*utf8 & 0x80)
				{
					int rune;

					utf8 += fz_chartorune(&rune, utf8);


					for (i = 0; i < font->cid_to_ucs_len && font->cid_to_ucs[i] != rune; i++)
						;


					if (i < font->cid_to_ucs_len)
						*bufp++ = i;
				}
				else
				{
					*bufp++ = *utf8++;
				}
			}

			*bufp = '\0';
		}
		fz_catch(ctx)
		{
			fz_free(ctx, buf);
			fz_rethrow(ctx);
		}

		return buf;
	}
	else
	{


		return fz_strdup(ctx, utf8);
	}
}
