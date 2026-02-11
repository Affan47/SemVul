M_AddToServerList (netadr_t adr, char *status_string)
{

	if(cls.key_dest != key_menu)
		return;

	if (m_num_servers == MAX_LOCAL_SERVERS)
		return;

	if(M_ParseServerInfo (adr, status_string, &mservers[m_num_servers]))
	{

		CON_Clear();

		m_num_servers++;
	}
}
