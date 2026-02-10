DoIconize(bool iconize)
{
	if (m_wndTaskbarNotifier && thePrefs::DoMinToTray()) {
		if (iconize) {


			if (SafeState()) {
				Show(false);
			}
		} else {
			Show(true);
			Raise();
		}
	} else {


	}
}
