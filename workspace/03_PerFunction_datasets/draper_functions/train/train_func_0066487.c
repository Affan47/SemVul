LoadCommandTable()
{
	char rawCommand[] = { 6, 0, 0x0a, 0, 0x40, 0, 0, 1, 0, 0 };

	Data command(rawCommand, sizeof(rawCommand));

	try {
		m_socket->Packet(command, m_response);

		MAKE_PACKET(rpack, m_response);
		while( rpack->command != SB_COMMAND_DB_DONE ) {
			m_socket->NextRecord(m_response);

			rpack = (const Protocol::Packet *) m_response.GetData();
			if( rpack->command == SB_COMMAND_DB_DATA && btohs(rpack->size) > 10 ) {


				m_commandTable.Clear();
				m_commandTable.Parse(m_response, 6);
			}
		}

		ddout(m_commandTable);

	}
	catch( Usb::Error & ) {
		eout(_("Desktop: error getting command table"));
		eeout(command, m_response);
		throw;
	}
}
