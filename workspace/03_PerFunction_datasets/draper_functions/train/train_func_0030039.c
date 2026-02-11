p_b_symbol(struct parse *p)
{
	char value;

	REQUIRE(MORE(), REG_EBRACK);
	if (!EATTWO('[', '.'))
		return(GETNEXT());


	value = p_b_coll_elem(p, '.');
	REQUIRE(EATTWO('.', ']'), REG_ECOLLATE);
	return(value);
}
