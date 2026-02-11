finditembytype(djitem* parent,int index,djson_type type)
{
	djitem* it = trueitem(parent);
	int i=0;
	while (it)
	{
		if (it->type==type)
		{
			if (i==index)
				return it;
			i++;
		}
		it = it->sibling;
	}
	return NULL;
}
