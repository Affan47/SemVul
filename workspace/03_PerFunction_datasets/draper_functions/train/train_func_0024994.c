GetListPtr(int a_list_num)
{
	if(a_list_num < 0)
		return NULL;

	if(a_list_num >= alist_count)
		return NULL;

	return alist_list[a_list_num];
}
