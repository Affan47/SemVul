adrbk_handy_stream(char *name)
{
    MAILSTREAM *stat_stream = NULL;
    int         i;

    dprint((9, "- adrbk_handy_stream(%s) -\n", name ? name : "?"));

    stat_stream = sp_stream_get(name, SP_SAME);


    for(i = 0; !stat_stream && i < as.n_addrbk; i++){
	PerAddrBook *pab;

	pab = &as.adrbks[i];

	if(pab->address_book &&
	   pab->address_book->type == Imap &&
	   pab->address_book->rd &&
	   pab->address_book->rd->type == RemImap &&
	   same_stream(name, pab->address_book->rd->t.i.stream)){
	    stat_stream = pab->address_book->rd->t.i.stream;
	    pab->address_book->rd->last_use = get_adj_time();
	    dprint((7,
		   "%s: used other abook stream for status (%ld)\n",
		   pab->address_book->orig_filename
		     ? pab->address_book->orig_filename : "?",
		   (long)pab->address_book->rd->last_use));
	}
    }

    dprint((9, "adrbk_handy_stream: returning %s\n",
	   stat_stream ? "good stream" : "NULL"));

    return(stat_stream);
}
