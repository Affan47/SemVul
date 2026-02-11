clear()
{
	int i;
	Explo *cur;
	Explo *del;

	for(i = 0; i < NumExploTypes; i++)
	{
		cur = exploRoot[i]->next;
		while(cur)
		{
			del = cur;
			cur = cur->next;
			killExplo(del);
		}
		exploRoot[i]->next = 0;
	}
}
