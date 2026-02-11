refreshExpanded(char *parent, bool ex)
{
	char *key;
	gTreeRow *row;


	row = tree->getRow(parent);
	row->updateExpanded(ex);
	if (!row->isExpanded())
		return;

	key = tree->getRow(parent)->child();
	if (!key)
		return;

	while (key)
	{

		row = tree->getRow(key);
		if (row->isExpanded())
		{
			row->setExpanded();
			refreshExpanded(key, true);
		}
		key = row->next();
	}
}
