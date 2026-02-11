GetTypeFromTypeSelection(int selection)
{
	if (selection < 0 || selection > (int)filter_type_map.size())
		selection = 0;

	return filter_type_map[selection];
}
