get_child_count(gContainer *ct)
{
	int i;
	int n = 0;

	for (i = 0; i < ct->childCount(); i++)
	{
		if (ct->child(i)->hFree)
			n++;
	}

	return n;
}
