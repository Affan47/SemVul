parse_acl_line(grecs_locus_t *locus, int allow, dicod_acl_t acl,
	       grecs_value_t *value)
{
    struct acl_entry *entry = xzalloc(sizeof(*entry));

    entry->locus = *locus;
    entry->locus.beg.file = strdup(entry->locus.beg.file);
    entry->locus.end.file = strdup(entry->locus.end.file);
    entry->allow = allow;

    switch (value->type) {
    case GRECS_TYPE_STRING:
	if (_parse_token (entry, value)) {
	    grecs_error(&entry->locus, 0, _("unknown word `%s'"),
			value->v.string);
	    return 1;
	}
	break;

    case GRECS_TYPE_ARRAY:
	if (_parse_acl(entry, value->v.arg.c, value->v.arg.v))
	    return 1;
	break;

    case GRECS_TYPE_LIST:
	grecs_error(locus, 0, _("unexpected list"));
	return 1;
    }
    xdico_list_append(acl->list, entry);
    return 0;
}
