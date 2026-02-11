validate_selected_unit_array(short* selectedUnitArray, short& selectedUnitCount)
{
	for( int i=0 ; i<selectedUnitCount ; i++ )
	{
		Unit* unitPtr;
		if( unit_array.is_deleted(selectedUnitArray[i]) ||
			!(unitPtr = unit_array[selectedUnitArray[i]]) ||
			!unitPtr->is_visible() || !unitPtr->is_nation(remote.nation_processing) )
		{
			memmove( selectedUnitArray+i, selectedUnitArray+i+1, sizeof(short) * (selectedUnitCount-i-1) );
			selectedUnitCount--;
			i--;
		}
	}
}
