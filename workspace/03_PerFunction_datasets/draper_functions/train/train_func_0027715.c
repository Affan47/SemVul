add_way_point(int pointX, int pointY, short* selectedArray, int selectedCount, char remoteAction)
{
	if(!remoteAction && remote.is_enable())
	{

		short *shortPtr = (short *)remote.new_send_queue_msg(MSG_UNIT_ADD_WAY_POINT,
			sizeof(short) * (3+selectedCount));
		shortPtr[0] = pointX;
		shortPtr[1] = pointY;
		shortPtr[2] = selectedCount;
		memcpy(shortPtr+3, selectedArray, sizeof(short)*selectedCount);
	}
	else
	{
		DWORD groupId = unit_array.cur_group_id;
		Unit *unitPtr;

		int i;
		for(i=0; i<selectedCount; ++i)
		{
			unitPtr = unit_array[selectedArray[i]];
			unitPtr->unit_group_id = groupId;
		}

		unit_array.cur_group_id++;

		for(i=0; i<selectedCount; ++i)
		{
			unitPtr = unit_array[selectedArray[i]];
			unitPtr->add_way_point(pointX, pointY);
		}
	}
}
