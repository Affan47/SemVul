ParseRecord(const Barry::DBData &data,
				const IConverter *ic)
{
	ios_format_state state(m_os);

	if( m_last_dbname != data.GetDBName() ) {
		m_os << _("Records for database: ") << data.GetDBName() << endl;
		m_last_dbname = data.GetDBName();
	}

	m_os << _("Raw record dump for record: ") << "0x"
		<< hex << data.GetUniqueId()
		<< ", " << _("type: ")
		<< "0x" << hex << (unsigned int) data.GetRecType()
		<< ", " << _("offset: ")
		<< "0x" << hex << data.GetOffset()
		<< endl;
	m_os << data.GetData() << endl;
}
