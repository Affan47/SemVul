threadDone() {
	modified = true;
	QGLE::setEnabled(rootButton, true);
	QGLE::setEnabled(searchButton, true);
	QGLE::setEnabled(locButton, true);
	QGLE::setEnabled(abortButton, true);
	if (mainWin != NULL) {
		string gsloc = getGLEInterface()->getGhostScriptLocation();
		QString loc = QString::fromUtf8(gsloc.c_str());
		tryGhostScriptLocation(loc);
	} else {
		okButton->setEnabled(true);
	}
}
