beforeClosing() {
	bool retval = true;

	for(int j = 0; j < m_stackTabWidget->count(); j++) {
		PartsBinPaletteWidget *bin = qobject_cast<PartsBinPaletteWidget*>(m_stackTabWidget->widget(j));
		if (bin && !bin->fastLoaded()) {
			setAsCurrentTab(bin);
			retval = retval && bin->beforeClosing();
			if(!retval) break;
		}
	}


	if(retval) {
		saveStateAndGeometry();
	}

	return retval;
}
