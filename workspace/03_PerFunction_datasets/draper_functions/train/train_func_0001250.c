hud_squadmsg_ship_order_valid( int shipnum, int order )
{

	Assert( shipnum >= 0 && shipnum < MAX_SHIPS );

	switch ( order  )
	{
		case DEPART_ITEM:

			if (Ships[shipnum].flags & SF_DISABLED)
				return 0;


			if (Ships[shipnum].flags2 & SF2_NO_SUBSPACE_DRIVE)
			{

				if (ship_get_ship_with_dock_bay(Ships[shipnum].team) < 0)
					return 0;
			}

			break;
	}
	return 1;
}
