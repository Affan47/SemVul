setItemExpanded(char *key, bool ex)
{
	gTreeRow *row = (*tree)[key];
	if (row->isExpanded() != ex)
  	row->setExpanded(ex);
}
