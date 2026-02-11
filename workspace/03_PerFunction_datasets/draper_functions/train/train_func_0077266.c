GetMuleVersion()
{
	wxString ver(wxT(VERSION));

#if 0
	ver += wxT(" compiled with ");
#else
	ver += wxString(_(" compiled with "));
#endif


	#if   defined(__WXGTK20__)
		ver += wxT("wxGTK2");
	#elif defined(__WXGTK__)
		ver += wxT("wxGTK1");

	#elif defined(__WXOSX_CARBON__)
		ver += wxT("wxOSX Carbon");
	#elif defined(__WXOSX_COCOA__)
		ver += wxT("wxOSX Cocoa");

	#elif defined(__WXCOCOA__)
		ver += wxT("wxCocoa");

	#elif defined(__WXMAC__)
		ver += wxT("wxMac");
	#elif defined(__WXMSW__) && defined(__VISUALC__)
		ver += wxT("wxMSW VC");
	#elif defined(__WXMSW__)
		ver += wxT("wxMSW");
	#endif

	ver += CFormat(wxT(" v%d.%d.%d")) % wxMAJOR_VERSION % wxMINOR_VERSION % wxRELEASE_NUMBER;

#ifdef __DEBUG__
	ver += wxT(" (Debugging)");
#endif

#ifdef SVNDATE
	ver += CFormat(wxT(" (Snapshot: %s)")) % wxT(SVNDATE);
#endif


	ver += wxT(" ");
	ver += ADU_MOD;


	return ver;
}
