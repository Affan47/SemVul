makefileindex(const char *file, STRBUF *a_files)
{
	STATIC_STRBUF(sb);
	FILE *filesop;
	int flags = REG_EXTENDED;


	char basedir[MAXPATHLEN+1];


	indexlink = (Fflag) ? "../files" : "../mains";
	src_count = 0;

	gp = gfind_open(dbpath, NULL, other_files ? GPATH_BOTH : GPATH_SOURCE);


	if (w32)
		flags |= REG_ICASE;
	strbuf_clear(sb);
	strbuf_puts(sb, "\\.(");
	{
		const char *p = include_file_suffixes;
		int c;

		while ((c = (unsigned char)*p++) != '\0') {
			if (isregexchar(c))
				strbuf_putc(sb, '\\');
			else if (c == ',')
				c = '|';
			strbuf_putc(sb, c);
		}
	}
	strbuf_puts(sb, ")$");
	if (regcomp(&is_include_file, strbuf_value(sb), flags) != 0)
		die("cannot compile regular expression '%s'.", strbuf_value(sb));


	if ((filesop = fopen(makepath(distpath, file, NULL), "w")) == NULL)
		die("cannot open file '%s'.", file);
	fputs_nl(gen_page_begin(title_file_index, TOPDIR), filesop);
	fputs_nl(body_begin, filesop);
	fputs(header_begin, filesop);
	fputs(gen_href_begin(NULL, "files", normal_suffix, NULL), filesop);
	fputs(title_file_index, filesop);
	fputs(gen_href_end(), filesop);
	fputs_nl(header_end, filesop);
	if (table_flist) {
		fputs_nl(flist_begin, filesop);
	} else if (!no_order_list) {
		fputs_nl(list_begin, filesop);
	}
	FILEMAP = NULL;
	if (map_file) {
		if (!(FILEMAP = fopen(makepath(distpath, "FILEMAP", NULL), "w")))
                        die("cannot open '%s'.", makepath(distpath, "FILEMAP", NULL));
	}


	files = a_files;
	strcpy(basedir, ".");
	(void)print_directory(0, basedir);

	if (map_file)
		fclose(FILEMAP);
	gfind_close(gp);
	regfree(&is_include_file);

	fputs(strbuf_value(files), filesop);
	if (table_flist)
		fputs_nl(flist_end, filesop);
	else if (!no_order_list)
		fputs_nl(list_end, filesop);
	else
		fputs_nl(br, filesop);
	fputs_nl(body_end, filesop);
	fputs_nl(gen_page_end(), filesop);
	fclose(filesop);
	html_count++;
	return src_count;
}
