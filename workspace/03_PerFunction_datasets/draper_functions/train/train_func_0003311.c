AssignIfExist(ec_tagname_t tagname, float &target) const
{
	const CECTag *tag = GetTagByName(tagname);
	if (tag) {
		target = tag->GetDoubleData();
		return true;
	}
	return false;
}
