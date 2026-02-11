temp_unlock()
{

	save_locked_flag = buf_locked;

	if( buf_locked )
		unlock_buf();

}
