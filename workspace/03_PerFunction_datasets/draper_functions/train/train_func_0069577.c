next_substitution(struct symbol *mac_symbol, const char *body_pos,
		  const char **next_match, struct macro_arg **match_marg,
		  regmatch_t *match)
{
	regmatch_t	  matches[2];
	struct macro_arg *marg;
	const char	 *search_pos;
	int		  retval;

	do {
		search_pos = *next_match;

		STAILQ_FOREACH(marg, &mac_symbol->info.macroinfo->args, links) {

			retval = regexec(&marg->arg_regex, search_pos, 2,
					 matches, 0);
			if (retval == 0
			 && (matches[1].rm_eo + search_pos) <= body_pos
			 && (matches[1].rm_eo + search_pos) > *next_match) {
				*match = matches[1];
				*next_match = match->rm_eo + search_pos;
				*match_marg = marg;
			}
		}
	} while (search_pos != *next_match);
}
