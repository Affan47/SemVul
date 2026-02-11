RemoveFirstItem()
{
	for (int i = 0; i < num_items-1; i++)
		list[i] = list[i+1];
	num_items--;
}
