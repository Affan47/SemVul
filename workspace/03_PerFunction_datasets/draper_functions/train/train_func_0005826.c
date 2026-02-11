selectNewFile()
{
	QString name = browse(newFileCB->currentText());
	if (!name.isEmpty())
		newFileCB->setEditText(name);
	changed();
}
