OnInit()
{
	amuledlg = NULL;

	if ( !CamuleApp::OnInit() ) {
		return false;
	}


	core_timer = new CTimer(this,ID_CORE_TIMER_EVENT);
	if (!core_timer) {
		AddLogLineCS(_("Fatal Error: Failed to create Core Timer"));
		OnExit();
	}


	core_timer->Start(CORE_TIMER_PERIOD);
	amuledlg->StartGuiTimer();

#ifdef __WXMAC__


	CFURLRef ed2kHelperUrl = CFBundleCopyAuxiliaryExecutableURL(
		CFBundleGetMainBundle(), CFSTR("ed2kHelperScript.app"));
	if (ed2kHelperUrl) {
		LSRegisterURL(ed2kHelperUrl, true);
		CFRelease(ed2kHelperUrl);
	}
#endif

	return true;
}
