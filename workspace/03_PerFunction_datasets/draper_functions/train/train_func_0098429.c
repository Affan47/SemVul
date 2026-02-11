unset_terminal()
{
    struct udvt_entry *original_terminal = get_udv_by_name("GNUTERM");

    if (multiplot)
	term_end_multiplot();

    term_reset();

    if (original_terminal) {
	char *termname = original_terminal->udv_value.v.string_val;
	term = change_term(termname, strlen(termname));
    }
    screen_ok = FALSE;
}
