GetRecordData(const std::string &recordId)
	{
		string data;

		Barry::RecordStateTable rst;
		m_desk.GetRecordStateTable(m_pdb->Number, rst);

		uint32_t recid = strtoul(recordId.c_str(), NULL, 16);
		RecordStateTable::IndexType index;
		if( rst.GetIndex(recid, &index) ) {
			ostringstream oss;
			ParserPtr parser = GetParser(m_pdb->Name, oss, false);
			m_desk.GetRecord(m_pdb->Number, index, *parser);
			data = oss.str();
		}

		return data;
	}
}
