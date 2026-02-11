_equalCreateOpClassItem(CreateOpClassItem *a, CreateOpClassItem *b)
{
	COMPARE_SCALAR_FIELD(itemtype);
	COMPARE_NODE_FIELD(name);
	COMPARE_NODE_FIELD(args);
	COMPARE_SCALAR_FIELD(number);
	COMPARE_SCALAR_FIELD(recheck);
	COMPARE_NODE_FIELD(storedtype);

	return true;
}
