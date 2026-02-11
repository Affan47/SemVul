group_units(int groupNum)
{
	err_when(groupNum<1 || groupNum>MAX_SELECT_GROUP_NUM);

	Unit	*unitPtr;
	int playerNation;

	if(!unit_array.selected_recno)
		return;
	else
	{
		playerNation = nation_array.player_recno;
		unitPtr = unit_array[unit_array.selected_recno];
		if(unitPtr->nation_recno!=playerNation)
			return;
	}


	int arraySize = unit_array.size();
	for(int i=arraySize; i>0; --i)
	{
		if(unit_array.is_deleted(i))
			continue;

		unitPtr = unit_array[i];
		if(unitPtr->nation_recno!=playerNation)
			continue;


		if(unitPtr->selected_flag)
				unitPtr->group_select_id = groupNum;
		else if(unitPtr->group_select_id==groupNum)
			unitPtr->group_select_id = 0;
	}
}
