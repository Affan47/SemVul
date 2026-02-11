SortServerList_Func ( void *_self )
{
	int column_num, i;
	menulist_s *self = (menulist_s *)_self;

	column_num = self-s_serverlist_header_columns;

	for (i = 0; i < SERVER_LIST_COLUMNS; i++)
		if (i != column_num)
			s_serverlist_header_columns[i].curvalue = 0;

	if (self->curvalue == 0)
	{
		if (column_num == 3)
		{
			self->curvalue = 1;
		}
		else
		{
			s_serverlist_header_columns[3].curvalue = 1;
			SortServerList_Func (&s_serverlist_header_columns[3]);
			return;
		}
	}

	QSortColumn = column_num;
	QSortReverse = self->curvalue == 2;

	qsort (s_serverlist_submenu.items, s_serverlist_submenu.nitems, sizeof (void*), SortServerList_Compare);
	s_serverlist_submenu.yscroll = 0;
}
