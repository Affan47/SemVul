verse_session_get(void)
{
	if(VConData.current_connection < VConData.con_count)
		return VConData.con[VConData.current_connection].out_queue;
	return NULL;
}
