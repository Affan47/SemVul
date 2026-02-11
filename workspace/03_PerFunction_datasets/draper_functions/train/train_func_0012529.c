getOpenFileNames( QWidget * parent, const QString & caption, const QString & dir, const QString & filter, QString * selectedFilter, QFileDialog::Options options )
{
	QStringList result = QFileDialog::getOpenFileNames(parent, caption, dir, filter, selectedFilter, options);
	if (result.count() > 0) {
		setOpenSaveFolder(result.at(0));
	}
	return result;
}
