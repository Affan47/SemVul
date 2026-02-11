offset_to_decorated_string(unsigned offset1, unsigned offset2) const
{
    Vector<LandmarkInfo>::const_iterator i =
	std::lower_bound(_linfo.begin(), _linfo.end(), offset1, li_searcher);
    if (i == _linfo.end())
	i = _linfo.begin();
    StringAccum sa;
    if (i != _linfo.end()) {
	const String &fname = _fnames[i->filename];
	if (fname && i->lineno)
	    sa << fname << ':' << i->lineno;
	else if (fname)
	    sa << fname;
	else if (i->lineno)
	    sa << "line " << i->lineno;
    }
    if (!sa)
	sa << "<unknown>";
    if (offset1 != LandmarkT::noffset) {
	String x = ErrorHandler::make_landmark_anno(sa.take_string());
	sa.clear();
	sa << x << "{l1:" << offset1 << "}{l2:" << offset2 << '}';
	return sa.take_string();
    } else
	return sa.take_string();
}
