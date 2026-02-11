GetCompilerFlags()
{
#ifndef USED_CXXFLAGS
	return _T("");
#else
	wxString flags(USED_CXXFLAGS, wxConvLocal);
	return flags;
#endif
}
