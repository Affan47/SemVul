GetNodeUseFlags(const NODE * node)
{
	int	i;
	USEFLAG	flags;

	flags = USE_NONE;


	switch (node->op)
	{
		case OP_COLUMN_BASE:
		case OP_COLUMN_SHOW:
		case OP_COLUMN_TEST:
			flags |= node->column->useFlag;
			break;

		case OP_FUNCTION:
			if (node->intVal == FUNC_MY)
				flags |= USE_SELF;

		default:
			break;
	}


	for (i = 0; i < CHILDS; i++)
	{
		if (node->child[i])
			flags |= GetNodeUseFlags(node->child[i]);
	}


	return flags;
}
