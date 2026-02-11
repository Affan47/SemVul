getWindowTitle( Window w ) const
{
	WindowManager::Property <char> p;

	if( !p.getProperty( display, w, XA_STRING, "WM_NAME" ) &&
		!p.getProperty( display, w,
			XInternAtom( display, "UTF8_STRING", False ),
			"_NET_WM_NAME" ) )
		return "";

	string s = p.getData();

	return s;
}
