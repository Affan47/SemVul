Seek(uint64_t Offset, CStream::TSeekOrigin Origin)
{
	if (!m_f.is_open()) return 0;

	fstream::off_type  offset = Offset;
	fstream::seekdir   way;

	switch(Origin)
	{
	case sFromBeginning: way = ios_base::beg; break;
	case sFromCurrent: way = ios_base::cur; break;
	case sFromEnd: way = ios_base::end; break;
	default: THROW_EXCEPTION("Invalid value for 'Origin'");
	}

	m_f.seekp(offset, way);
	m_f.seekg(offset, way);

	return getPosition();
}
