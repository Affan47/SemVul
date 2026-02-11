restoreDocks() {
	for (int i = 0; i < children().count(); i++) {
		FDockWidget * dock = qobject_cast<FDockWidget *>(children()[i]);
		if (dock == NULL) continue;


		dock->restoreState();
	}
}
