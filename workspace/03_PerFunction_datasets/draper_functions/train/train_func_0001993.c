pdfapp_oncopy(pdfapp_t *app, unsigned short *ucsbuf, int ucslen)
{
	fz_bbox hitbox;
	fz_matrix ctm;
	fz_text_page *page = app->page_text;
	fz_text_block *block;
	fz_text_line *line;
	fz_text_span *span;
	int c, i, p;
	int seen = 0;

	int x0 = app->selr.x0;
	int x1 = app->selr.x1;
	int y0 = app->selr.y0;
	int y1 = app->selr.y1;

	ctm = pdfapp_viewctm(app);

	p = 0;

	for (block = page->blocks; block < page->blocks + page->len; block++)
	{
		for (line = block->lines; line < block->lines + block->len; line++)
		{
			for (span = line->spans; span < line->spans + line->len; span++)
			{
				if (seen)
				{
#ifdef _WIN32
					if (p < ucslen - 1)
						ucsbuf[p++] = '\r';
#endif
					if (p < ucslen - 1)
						ucsbuf[p++] = '\n';
				}

				seen = 0;

				for (i = 0; i < span->len; i++)
				{
					hitbox = fz_bbox_covering_rect(span->text[i].bbox);
					hitbox = fz_transform_bbox(ctm, hitbox);
					c = span->text[i].c;
					if (c < 32)
						c = '?';
					if (hitbox.x1 >= x0 && hitbox.x0 <= x1 && hitbox.y1 >= y0 && hitbox.y0 <= y1)
					{
						if (p < ucslen - 1)
							ucsbuf[p++] = c;
						seen = 1;
					}
				}

				seen = (seen && span + 1 == line->spans + line->len);
			}
		}
	}

	ucsbuf[p] = 0;
}
