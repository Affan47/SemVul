set_alternating_send(int rate)
{
	if( rate <= 0 || rate > 100 || (sync_test_level != 0 && rate != 1) )
	{
		err_here();


	}
	else
		alternating_send_rate = rate;
}
