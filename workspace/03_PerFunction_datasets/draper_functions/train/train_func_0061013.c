name(int symbol)
{
	if(check_symbol(symbol) < 0)
		return "<key does not exist!>";
	if(table[symbol]->name)
		return table[symbol]->name;
	else
		return "<key has no name>";
}
