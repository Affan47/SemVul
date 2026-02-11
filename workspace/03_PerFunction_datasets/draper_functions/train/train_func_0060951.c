my_getExistingDirectory()
{
	QFileDialog dialog(qApp->activeWindow(), dialog_title, dialog_path);

	dialog.setMode(QFileDialog::Directory);
	dialog.setOption(QFileDialog::DontUseNativeDialog);

	if (dialog.exec() == QDialog::Accepted)
		return dialog.selectedFiles().value(0);
	else
		return QString();
}
