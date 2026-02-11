cvs_file_add_symbol(CvsFile * file, const char * rev_str, const char * p_tag_str)
{
    CvsFileRevision * rev;
    GlobalSymbol * sym;
    Tag * tag;


    char * tag_str = get_string(p_tag_str);

    debug(DEBUG_STATUS, "adding symbol to file: %s %s->%s", file->filename, tag_str, rev_str);
    rev = cvs_file_add_revision(file, rev_str);
    put_hash_object_ex(file->symbols, tag_str, rev, HT_NO_KEYCOPY, NULL, NULL);


    sym = (GlobalSymbol*)get_hash_object(global_symbols, tag_str);
    if (!sym)
    {
	sym = (GlobalSymbol*)malloc(sizeof(*sym));
	sym->tag = tag_str;
	sym->ps = NULL;
	INIT_LIST_HEAD(&sym->tags);

	put_hash_object_ex(global_symbols, sym->tag, sym, HT_NO_KEYCOPY, NULL, NULL);
    }

    tag = (Tag*)malloc(sizeof(*tag));
    tag->tag = tag_str;
    tag->rev = rev;
    tag->sym = sym;
    list_add(&tag->global_link, &sym->tags);
    list_add(&tag->rev_link, &rev->tags);
}
