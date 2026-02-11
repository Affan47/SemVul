new_line(unsigned offset, const String &filename, unsigned lineno)
{
    if (_fnames.size() == 0 || _fnames.back() != filename)
	_fnames.push_back(filename);
    if (_linfo.size())
	_linfo.back().end_offset = offset;
    _linfo.push_back(LandmarkInfo(LandmarkT::noffset - 1, _fnames.size() - 1, lineno));
}
