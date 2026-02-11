searchKeyword(char const * const tag) const
{
	LexerKeyword search_tag = { tag, 0 };
	LexerKeyword * res =
		lower_bound(table, table + no_items,
			    search_tag, CompareTags());


	if (res != table + no_items
	    && !compare_ascii_no_case(res->tag, tag))
		return res->code;
	return LEX_UNDEF;
}
