reset()
{
	init();

	elem = QDomElement();
	elemDoc = QDomDocument();
	tagOpen = QString();
	tagClose = QString();
	xml.reset();
	outData.resize(0);
	trackQueue.clear();
	transferItemList.clear();
}
