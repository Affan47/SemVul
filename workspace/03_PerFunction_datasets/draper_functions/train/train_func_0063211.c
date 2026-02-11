generate_template_type(const char *varname,
		       const char **dupname,
		       const char *symname,
		       const char *basetype,
		       const char *name,
		       Type *type,
		       int optional, int isstruct, int need_offset)
{
    struct tlist *tl;
    const char *dup;
    int have_ellipsis = 0;
    int implicit = 0;

    tl = tlist_new(varname);

    if (type->type == TTag)
	implicit = (type->tag.tagenv == TE_IMPLICIT);

    fprintf(get_code_file(), "extern const struct asn1_template asn1_%s[];\n", tl->name);

    template_members(&tl->template, basetype, name, type, optional, implicit, isstruct, need_offset);


    if (type->type == TSequence || type->type == TSet) {
	Member *m;
	ASN1_TAILQ_FOREACH(m, type->members, members) {
	    if (m->ellipsis)
		have_ellipsis = 1;
	}
    }

    if (ASN1_TAILQ_EMPTY(&tl->template) && compact_tag(type)->type != TNull)
	errx(1, "Tag %s...%s with no content ?", basetype, name ? name : "");

    fprintf(get_code_file(), "/* generate_template_type: %s */\n", tl->name);

    tlist_header(tl, "{ 0%s%s, sizeof(%s%s), ((void *)%lu) }",
		 (symname && preserve_type(symname)) ? "|A1_HF_PRESERVE" : "",
		 have_ellipsis ? "|A1_HF_ELLIPSIS" : "",
		 isstruct ? "struct " : "", basetype, tlist_count(tl));

    dup = tlist_find_dup(tl);
    if (dup) {
#if 0
	if (strcmp(dup, tl->name) == 0)
	    errx(1, "found dup of ourself: %s", dup);
#endif
	*dupname = dup;
    } else {
	*dupname = tl->name;
	tlist_print(tl);
	tlist_add(tl);
    }
}
