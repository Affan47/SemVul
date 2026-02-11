openData(const string& name, const string& lab) throw(ParserError) {
	m_DatFile = validate_fopen(name, "w", false);
	m_LabFile = validate_fopen(lab, "w", false);
}
