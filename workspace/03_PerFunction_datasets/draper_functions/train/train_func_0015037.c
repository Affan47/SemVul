sam_hdr_find_key(SAM_hdr *sh,
			      SAM_hdr_type *type,
			      char *key,
			      SAM_hdr_tag **prev) {
    SAM_hdr_tag *tag, *p = NULL;

    for (tag = type->tag; tag; p = tag, tag = tag->next) {
	if (tag->str[0] == key[0] && tag->str[1] == key[1]) {
	    if (prev)
		*prev = p;
	    return tag;
	}
    }

    if (prev)
	*prev = p;

    return NULL;
}
