nameChanged(const QString &newname)
{
	holeInfo->setName(newname);
	holeInfo->setUntranslatedName(newname);
	changed();
}
