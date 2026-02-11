AssignIfExist(ec_tagname_t tagname, wxString *target) const
{
	wxString ret;
	const CECTag *tag = GetTagByName(tagname);
	if (tag) {
		ret = tag->GetStringData();
		if (target) {
			*target = ret;
		}
	}
	return ret;
}
