pasteActions(int row)
{
	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();

	dropMimeData(mimeData, Qt::CopyAction, row, 0, QModelIndex());
}
