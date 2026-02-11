showDiagnosticText(const QString& event, const QString& diagnostic)
{
	while (1) {
		QMessageBox msgbox(QMessageBox::Critical,
		                   tr("Error"),
		                   event,
		                   QMessageBox::Ok, 0);
		QPushButton *diag = msgbox.addButton(tr("Diagnostics"), QMessageBox::HelpRole);
		msgbox.exec();
		if (msgbox.clickedButton() == diag) {
			ShowTextDlg* w = new ShowTextDlg(diagnostic, true, false, 0);
			w->setWindowTitle(tr("OpenPGP Diagnostic Text"));
			w->resize(560, 240);
			w->exec();

			continue;
		}
		else {
			break;
		}
	}
}
