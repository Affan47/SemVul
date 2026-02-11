set_relation_should_attack(short nationRecno, char newValue, char remoteAction)
{
	if( !remoteAction && remote.is_enable() )
	{
		short *shortPtr = (short *) remote.new_send_queue_msg(MSG_NATION_SET_SHOULD_ATTACK, 3*sizeof(short));
		*shortPtr = nation_recno;
		shortPtr[1] = nationRecno;
		shortPtr[2] = newValue;
	}
	else
	{
		relation_should_attack_array[nationRecno-1] = newValue;
		get_relation(nationRecno)->should_attack    = newValue;
	}
}
