el_end(EditLine *el)
{

	if (el == NULL)
		return;

	el_reset(el);

	terminal_end(el);
	keymacro_end(el);
	map_end(el);
	tty_end(el);
	ch_end(el);
	search_end(el);
	hist_end(el);
	prompt_end(el);
	sig_end(el);

	el_free(el->el_prog);
#ifdef WIDECHAR
	el_free(el->el_scratch.cbuff);
	el_free(el->el_scratch.wbuff);
	el_free(el->el_lgcyconv.cbuff);
	el_free(el->el_lgcyconv.wbuff);
#endif
	el_free(el);
}
