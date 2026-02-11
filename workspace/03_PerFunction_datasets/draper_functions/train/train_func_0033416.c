GetLink() const
{
	STRING retval(_T("magnet:"));

	for (List_Type::const_iterator it = m_fields.begin(); it != m_fields.end(); ++it) {
		if (it == m_fields.begin()) {
			retval.append(1, _C('?'));
		} else {
			retval.append(1, _C('&'));
		}
		retval.append(it->first);
		retval.append(1, _C('='));
		retval.append(it->second);
	}
	return retval;
}
