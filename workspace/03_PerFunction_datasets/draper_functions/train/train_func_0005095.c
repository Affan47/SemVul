spell_free_all()
{
    slang_T	*slang;
    buf_T	*buf;
    char_u	fname[MAXPATHL];


    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	ga_clear(&buf->b_s.b_langp);

    while (first_lang != NULL)
    {
	slang = first_lang;
	first_lang = slang->sl_next;
	slang_free(slang);
    }

    if (int_wordlist != NULL)
    {

	mch_remove(int_wordlist);
	int_wordlist_spl(fname);
	mch_remove(fname);
	vim_free(int_wordlist);
	int_wordlist = NULL;
    }

    init_spell_chartab();

    vim_free(repl_to);
    repl_to = NULL;
    vim_free(repl_from);
    repl_from = NULL;
}
