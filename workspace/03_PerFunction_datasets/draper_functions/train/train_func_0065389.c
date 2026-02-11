sort(bool ascending)
{
	if (ascending)
		std::sort(items.begin(), items.end(), list_item_ptr_less);
	else
		std::sort(items.begin(), items.end(), list_item_ptr_greater);
}
