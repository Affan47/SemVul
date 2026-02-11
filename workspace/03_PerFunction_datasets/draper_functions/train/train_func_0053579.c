unload_all_units(char remoteAction)
{
	if(!remoteAction && remote.is_enable() )
	{

		short *shortPtr = (short *)remote.new_send_queue_msg(MSG_U_SHIP_UNLOAD_ALL_UNITS, sizeof(short));
		*shortPtr = sprite_recno;
		return;
	}

	unloading_unit(1);
}
