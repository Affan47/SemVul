onRestoreDefaults() {
	if (QMessageBox::information(w, CAP(tr("Restore default shortcuts")),
                   tr("Are you sure you would like to restore the default shortcuts?"),
                   QMessageBox::Yes | QMessageBox::No,
                   QMessageBox::No) == QMessageBox::Yes) {

		OptShortcutsUI *d = (OptShortcutsUI *)w;
		d->treeShortcuts->clear();
		readShortcuts(PsiOptions::defaults());
		emit dataChanged();
	}
}
