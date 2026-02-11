help (int argc,char **argv, void *data)
{
	if (argc == 1) {
		ItemT *titem = items;

		cli_outfunf ("available commands:");

		while (titem) {
		#ifdef HIDE_NULL_HELP
			if(titem->usage)
		#endif
			if (is_command (titem))
				cli_outfunf ("%14s %s", titem->name, titem->usage);
			titem = titem->next;
		};
	} else {
		ItemT *titem = items;

		cli_outfunf ("HELP for '%s'", argv[1] );

		while (titem) {
			if (is_command (titem)) {
				if (!strcmp (argv[1], titem->name)) {
					cli_outfunf ("usage: %s %s", titem->name, titem->usage);
					if(titem->help[0]){
						cli_outfun ("");
						cli_outfun(titem->help);
					}
					return data;
				}
			}
			titem = titem->next;
		}
		cli_outfunf ("unknown command '%s'", argv[1]);
	}
	return data;
}
