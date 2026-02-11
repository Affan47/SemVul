config_rejoin_quote(struct list_head *head)
{
	struct ptoken *t, *n, *last = NULL;

	list_for_each_entry_safe(t, n, head, list)
	{
		if(!last)
			goto next_round;

		if(!(t->is_quote && last->is_quote))
			goto next_round;

		if(t->quote_char != last->quote_char)
			goto next_round;

		if(!config_ptoken_concat(last, t))
			return false;
		last->is_quote_closed |= t->is_quote_closed;
		list_del(&t->list);
		config_ptoken_free(t);
next_round:
		last = t;
	}
	return true;
}
