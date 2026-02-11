button_down()
{
	if ( (m_flags & BF_DOWN) || !timestamp_elapsed(m_press_linger) )
		return TRUE;
	else
 		return FALSE;
}
