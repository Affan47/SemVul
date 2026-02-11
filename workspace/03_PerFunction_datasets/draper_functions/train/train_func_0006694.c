GetFloatTagValue(const wxString& tagname) const
{
	for (TagPtrList::const_iterator it = m_taglist.begin(); it != m_taglist.end(); ++it) {
		if ((*it)->IsFloat() && ((*it)->GetName() == tagname)) {
			return (*it)->GetFloat();
		}
	}
	return 0.0f;
}
