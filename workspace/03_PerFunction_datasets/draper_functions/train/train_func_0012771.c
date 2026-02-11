print_text(int end, struct gcide_tag *tag, void *data)
{
    struct output_closure *clos = data;
    static char *quote[2] = { "``", "''" };
    static char *ref[2] = { "{" , "}" };

    switch (tag->tag_type) {
    case gcide_content_unspecified:
	break;
    case gcide_content_text:
	if (clos->flags & GOF_IGNORE)
	    break;
	if (clos->flags & GOF_AS) {
	    char *s = tag->tag_v.text;

	    if (strncmp(s, "as", 2) == 0 &&
		(isspace(s[3]) || ispunct(s[3]))) {
		fwrite(s, 3, 1, clos->stream);
		for (s += 3; *s && isspace(*s); s++)
		    fputc(*s, clos->stream);
		fprintf(clos->stream, "%s%s", quote[0], s);
	    } else
		fprintf(clos->stream, "%s", quote[0]);
	} else
	    fprintf(clos->stream, "%s", tag->tag_v.text);
	break;
    case gcide_content_taglist:
	if (tag->tag_parmc) {
	    clos->flags &= ~GOF_AS;
	    if (end) {
		if (strcmp(tag->tag_name, "pr") == 0 &&
			 clos->flags & GCIDE_NOPR)
		    clos->flags &= ~GOF_IGNORE;
		else if (clos->flags & GOF_IGNORE)
		    break;
		else if (strcmp(tag->tag_name, "as") == 0)
		    fprintf(clos->stream, "%s", quote[1]);
		else if (strcmp(tag->tag_name, "er") == 0)
		    fprintf(clos->stream, "%s", ref[1]);
	    } else {
		if (strcmp(tag->tag_name, "pr") == 0 &&
			 clos->flags & GCIDE_NOPR)
		    clos->flags |= GOF_IGNORE;
		else if (clos->flags & GOF_IGNORE)
		    break;
		else if (strcmp(tag->tag_name, "sn") == 0)
		    fputc('\n', clos->stream);
		else if (strcmp(tag->tag_name, "as") == 0)
		    clos->flags |= GOF_AS;
		else if (strcmp(tag->tag_name, "er") == 0)
		    fprintf(clos->stream, "%s", ref[0]);
	    }
	}
    }
    return 0;
}
