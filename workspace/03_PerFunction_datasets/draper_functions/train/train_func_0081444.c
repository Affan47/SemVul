NextItemBrackets(int type, int control)
{


	int value;

	if((control & 1) == 0)
	{
		if(!NextItem(tOPENBRACKET))
		{
			error("Expected '('", NULL);
		}
	}

	value = NextItem(type);
	if((control & 2) && (item_terminator == ','))
		return(value);

	if(item_terminator != ')')
	{
		error("Expected ')'", NULL);
	}
	return(value);

}
