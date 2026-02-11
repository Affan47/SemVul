setItemSelected(char *key, bool vl)
{
	if (key)
	{
		if (vl && mode() == SELECT_SINGLE)
			tree->setCursor(key);
		tree->setRowSelected(key, vl);
	}
}
