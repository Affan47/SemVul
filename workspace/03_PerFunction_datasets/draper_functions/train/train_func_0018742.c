Safe_Delete()
{
	CUpDownClient * client = m_client;
	if (client) {
		Unlink();
		client->Safe_Delete();
	}
}
