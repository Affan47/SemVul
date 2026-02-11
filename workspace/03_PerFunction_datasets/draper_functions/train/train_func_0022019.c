vs_set_next_session(void)
{
	if(++VSConnectionStorage.current_session >= VSConnectionStorage.connection_length)
		VSConnectionStorage.current_session = 0;
	if(VSConnectionStorage.connection_length != 0)
		verse_session_set(VSConnectionStorage.connection[VSConnectionStorage.current_session].session);
}
