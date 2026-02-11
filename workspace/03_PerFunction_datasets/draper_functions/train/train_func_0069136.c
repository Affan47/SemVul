replace(query, inreg)
bool	query,
	inreg;
{
	LinePtr	l1 = curline,
		l2 = curbuf->b_last;
	int	char1 = curchar,
		char2 = length(curbuf->b_last),
		numdone;
	struct RE_block	re_blk;

	if (inreg) {
		Mark	*m = CurMark();

		l2 = m->m_line;
		char2 = m->m_char;
		(void) fixorder(&l1, &char1, &l2, &char2);
	}


	jamstr(rep_search,
		ask(rep_search[0] ? rep_search : (char *)NULL, ProcFmt));
	REcompile(rep_search, UseRE, &re_blk);


	{
		const char	*rp = do_ask("\r\n",
			NULL_ASK_EXT, rep_str, ": %f %s with ", rep_search);

		jamstr(rep_str, rp == NULL? NullStr : rp);
	}

	if ((numdone = substitute(&re_blk, query, l1, char1, l2, char2)) != 0
	&& !inreg)
	{
		do_set_mark(l1, char1);
		add_mess(" ");
	} else {
		message(NullStr);
	}
	add_mess("(%d substitution%n)", numdone, numdone);
}
