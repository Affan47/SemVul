renameBin() {
	PartsBinPaletteWidget * bin = currentBin();
	if (bin == NULL) return;

	if (!currentBin()->allowsChanges()) {

		QMessageBox::warning(this, tr("Read-only bin"), tr("This bin cannot be renamed."));
		return;
	}

	bool ok;
	QString newTitle = QInputDialog::getText(
		this,
		tr("Rename bin"),
		tr("Please choose a name for the bin:"),
		QLineEdit::Normal,
		bin->title(),
		&ok
	);
	if(ok) {
		bin->setTitle(newTitle);
		m_stackTabWidget->stackTabBar()->setTabToolTip(m_stackTabWidget->currentIndex(), newTitle);
		bin->addPartToMeAction()->setText(newTitle);
		updateTitle(bin, newTitle);
	}
}
