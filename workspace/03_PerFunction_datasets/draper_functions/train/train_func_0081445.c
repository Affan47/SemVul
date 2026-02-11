print_includes(void)
{
	gboolean found_header;
	char *p;


	if ( ! g_list_find_custom(include_files, "string.h", (GCompareFunc)strcmp)) {
		out_printf(out, "#include <string.h> /* memset() */\n\n");
	}

	p = g_strconcat(filebase, ".h", NULL);
	found_header = TRUE;
	if( ! g_list_find_custom(include_files, p, (GCompareFunc)strcmp)) {
		out_printf(out, "#include \"%s.h\"\n\n", filebase);
		found_header = FALSE;
	}
	g_free(p);


	if(outph) {
		char sep[2] = {0,0};
		if (file_sep != 0)
			sep[0] = file_sep;
		p = g_strconcat(filebase, sep, "private.h", NULL);
		if( ! g_list_find_custom(include_files, p,
					 (GCompareFunc)strcmp)) {
			out_printf(out, "#include \"%s%sprivate.h\"\n\n",
				   filebase,
				   sep);
			if(found_header)
				error_printf(GOB_WARN, 0,
					    "Implicit private header include "
					    "added to top of\n"
					    "\tsource file, while public "
					    "header is at a custom location, "
					    "you should\n"
					    "\texplicitly include "
					    "the private header below the "
					    "public one.");
		}
		g_free(p);
	}
}
