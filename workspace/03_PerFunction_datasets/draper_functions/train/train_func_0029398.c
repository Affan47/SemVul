dicod_define_word_db(dicod_database_t *db, dico_stream_t stream,
		     const char *word)
{
    struct dico_database_module *mp = db->instance->module;
    dico_result_t res;
    size_t count;

    begin_timing("define");

    res = mp->dico_define(db->mod_handle, word);
    if (!res) {
	access_log_status(nomatch, nomatch);
	dico_stream_writeln(stream, nomatch, nomatch_len);
	return;
    }

    count = mp->dico_result_count(res);
    if (count == 0) {
	access_log_status(nomatch, nomatch);
	dico_stream_writeln(stream, nomatch, nomatch_len);
    } else {
	current_stat.defines = count;
	if (mp->dico_compare_count)
	    current_stat.compares = mp->dico_compare_count(res);
	stream_printf(stream, "150 %lu definitions found: list follows\n",
		      (unsigned long) count);
	print_definitions(db, res, word, stream, NULL, count);
	stream_writez(stream, "250 Command complete");
	report_current_timing(stream, "define");
	dico_stream_write(stream, "\n", 1);
	access_log_status("150", "250");
    }

    mp->dico_free_result(res);
}
