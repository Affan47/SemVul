html_screenshot(const char *name, int mode)
{
	int y, x;
	int wid, hgt;

	byte a = TERM_WHITE;
	byte oa = TERM_WHITE;
	wchar_t c = L' ';

	const char *new_color_fmt = (mode == 0) ?
					"<font color=\"#%02X%02X%02X\">"
				 	: "[COLOR=\"#%02X%02X%02X\"]";
	const char *change_color_fmt = (mode == 0) ?
					"</font><font color=\"#%02X%02X%02X\">"
					: "[/COLOR][COLOR=\"#%02X%02X%02X\"]";
	const char *close_color_fmt = mode ==  0 ? "</font>" : "[/COLOR]";

	ang_file *fp;
	char buf[1024];


	path_build(buf, sizeof(buf), ANGBAND_DIR_USER, name);
	fp = file_open(buf, MODE_WRITE, FTYPE_TEXT);


	if (!fp)
	{
		plog_fmt("Cannot write the '%s' file!", buf);
		return;
	}


	Term_get_size(&wid, &hgt);

	if (mode == 0)
	{
		file_putf(fp, "<!DOCTYPE html><html><head>\n");
		file_putf(fp, "  <meta='generator' content='%s'>\n", buildid);
		file_putf(fp, "  <title>%s</title>\n", name);
		file_putf(fp, "</head>\n\n");
		file_putf(fp, "<body style='color: #fff; background: #000;'>\n");
		file_putf(fp, "<pre>\n");
	}
	else
	{
		file_putf(fp, "[CODE][TT][BC=black][COLOR=white]\n");
	}


	for (y = 0; y < hgt; y++)
	{
		for (x = 0; x < wid; x++)
		{

			(void)(Term_what(x, y, &a, &c));


			if (oa != a && c != L' ')
			{

				if (oa == TERM_WHITE)
				{
					file_putf(fp, new_color_fmt,
					        angband_color_table[a][1],
					        angband_color_table[a][2],
					        angband_color_table[a][3]);
				}


				else if (a == TERM_WHITE)
				{
					file_putf(fp, close_color_fmt);
				}


				else
				{
					file_putf(fp, change_color_fmt,
					        angband_color_table[a][1],
					        angband_color_table[a][2],
					        angband_color_table[a][3]);
				}


				oa = a;
			}


			if (mode == 0) write_html_escape_char(fp, c);
			else
			{
				char mbseq[MB_LEN_MAX+1] = {0};
				wctomb(mbseq, c);
				file_putf(fp, "%s", mbseq);
			}
		}


		file_putf(fp, "\n");
	}


	if (oa != TERM_WHITE) file_putf(fp, close_color_fmt);

	if (mode == 0)
	{
		file_putf(fp, "</pre>\n");
		file_putf(fp, "</body>\n");
		file_putf(fp, "</html>\n");
	}
	else
	{
		file_putf(fp, "[/COLOR][/BC][/TT][/CODE]\n");
	}


	file_close(fp);
}
