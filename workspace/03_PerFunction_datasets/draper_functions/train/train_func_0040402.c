dicod_word_all(dico_stream_t stream, const char *word,
	       const dico_strategy_t strat,
	       const char *begfmt, const char *endmsg,
	       outproc_t proc, void *data, const char *tid)
{
    dicod_database_t *db;
    dico_iterator_t itr;
    dico_list_t reslist = xdico_list_create();
    size_t total = 0;
    struct dbres *rp;

    begin_timing(tid);

    if (strat && stratcl_check_word(strat->stratcl, word)) {
	access_log_status(nomatch, nomatch);
	dico_stream_writeln(stream, nomatch, nomatch_len);
	return;
    }

    itr = xdico_list_iterator(database_list);
    for (db = dico_iterator_first(itr); db; db = dico_iterator_next(itr)) {
	if (database_visible_p(db)) {
	    struct dico_database_module *mp = db->instance->module;
	    dico_result_t res = strat ?
		              mp->dico_match(db->mod_handle, strat, word) :
		              mp->dico_define(db->mod_handle, word);
	    size_t count;

	    if (!res)
		continue;
	    count = mp->dico_result_count(res);
	    if (!count) {
		mp->dico_free_result(res);
		continue;
	    }

	    total += count;
	    if (mp->dico_compare_count)
		current_stat.compares += mp->dico_compare_count(res);
	    rp = xmalloc(sizeof(*rp));
	    rp->db = db;
	    rp->res = res;
	    rp->count = count;
	    xdico_list_append(reslist, rp);
	}
    }

    dico_iterator_destroy(&itr);

    if (total == 0) {
	access_log_status(nomatch, nomatch);
	dico_stream_writeln(stream, nomatch, nomatch_len);
    } else {
	itr = xdico_list_iterator(reslist);

	if (strat)
	    current_stat.matches = total;
	else
	    current_stat.defines = total;
	stream_printf(stream, begfmt, (unsigned long) total);
	for (rp = dico_iterator_first(itr); rp; rp = dico_iterator_next(itr)) {
	    proc(rp->db, rp->res, word, stream, data, rp->count);
	    rp->db->instance->module->dico_free_result(rp->res);
	    free(rp);
	}
	stream_writez(stream, (char*) endmsg);
	report_current_timing(stream, tid);
	dico_stream_write(stream, "\n", 1);
	dico_iterator_destroy(&itr);
	access_log_status(begfmt, endmsg);
    }
    dico_list_destroy(&reslist);
}
