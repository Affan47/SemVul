limit_needed(Query *parse)
{
	Node	   *node;

	node = parse->limitCount;
	if (node)
	{
		if (IsA(node, Const))
		{

			if (!((Const *) node)->constisnull)
				return true;
		}
		else
			return true;
	}

	node = parse->limitOffset;
	if (node)
	{
		if (IsA(node, Const))
		{

			if (!((Const *) node)->constisnull)
			{
				int64		offset = DatumGetInt64(((Const *) node)->constvalue);

				if (offset != 0)
					return true;
			}
		}
		else
			return true;
	}

	return false;
}
