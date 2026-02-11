whine(change::pointer cp, string_list_ty *modifier)
{
    html_header(0, cp);
    printf("<title>Project ");
    html_encode_string(project_name_get(cp->pp));
    if (!cp->bogus)
	printf(", Change %ld", magic_zero_decode(cp->number));
    printf(",<br>\nPuzzlement</title></head><body>\n");
    html_header_ps(0, cp);
    printf("<h1 align=center>");
    emit_change(cp);
    printf(",<br>\nPuzzlement</h1>\n");
    printf("File information selector ");
    if (modifier->nstrings)
    {
	printf("&ldquo;<tt>");
	html_encode_string(modifier->string[0]);
	printf("</tt>&rdquo; ");
    }
    printf("not recognised.\n");
    printf("Please select one of the following:\n");
    printf("<ul>\n");
    for (const table_ty *tp = table; tp < ENDOF(table); ++tp)
    {
	if (tp->hide_me)
	    continue;
	string_ty *s = str_format("file+%s", tp->name);
	printf("<li>");
	emit_change_href(cp, s->str_text);
	printf("%s</a>\n", tp->name);
	str_free(s);
    }
    printf("</ul>\n");

    printf("<hr>\n");
    printf("<p align=\"center\" class=\"navbar\">[\n");
    printf("<a href=\"%s/\">Project List</a> |\n", http_script_name());
    emit_project_href(cp->pp, "menu");
    printf("Project Menu</a> |\n");
    emit_change_href(cp, "menu");
    printf("Change List</a> |\n");
    emit_change_href(cp, "menu");
    printf("Change Menu</a>\n");
    printf("]</p>\n");

    html_footer(0, cp);
}
