genius_got_etree (GelETree *e)
{
	if (e != NULL) {
		calc_running ++;
		check_events();
		gel_evalexp_parsed (e, gel_main_out, "= \e[1;36m", TRUE);
		gel_test_max_nodes_again ();
		calc_running --;
		gel_output_full_string (gel_main_out, "\e[0m");
		gel_output_flush (gel_main_out);
	}

	gel_printout_infos ();

	if (gel_got_eof) {
		gel_output_full_string (gel_main_out, "\n");
		gel_output_flush (gel_main_out);
		gel_got_eof = FALSE;
		gtk_main_quit();
	}
}
