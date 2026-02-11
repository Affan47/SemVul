unicode_lc(unicode_char c)
{
	unsigned i=find_case(c);

	return (unicode_case_tab[i][0] != c ? c:unicode_case_tab[i][2]);
}
