update_selected_trade_unit_info()
{
	short playerNationRecno = nation_array.player_recno;

	Unit *unitPtr;
	UnitMarine *marinePtr;
	if(remote.is_enable())
	{
		for(int i=size(); i>0; --i)
		{
			if(is_deleted(i))
				continue;

			unitPtr = (Unit*)get_ptr(i);
			if(!unitPtr->is_visible())
				continue;

			switch(unitPtr->unit_id)
			{
				case UNIT_CARAVAN:
						if(mp_is_selected_caravan(i))
							((UnitCaravan*) unitPtr)->update_stop_and_goods_info();
						break;

				case UNIT_VESSEL: case UNIT_CARAVEL: case UNIT_GALLEON:
						marinePtr = ((UnitMarine*) unitPtr);
						if(marinePtr->auto_mode && mp_is_selected_ship(i))
							marinePtr->update_stop_and_goods_info();
						break;

				default: break;
			}
		}
	}
	else if(selected_recno && !is_deleted(selected_recno))
	{
		unitPtr = (Unit*)get_ptr(selected_recno);
		if(unitPtr->nation_recno==playerNationRecno || config.show_ai_info)
		{
			switch(unitPtr->unit_id)
			{
				case UNIT_CARAVAN:
					((UnitCaravan*) unitPtr)->update_stop_and_goods_info();
					break;

				case UNIT_VESSEL: case UNIT_CARAVEL: case UNIT_GALLEON:
					marinePtr = ((UnitMarine*) unitPtr);
					if(marinePtr->auto_mode)
						marinePtr->update_stop_and_goods_info();
					break;

				default:
					break;
			}
		}
	}
}
