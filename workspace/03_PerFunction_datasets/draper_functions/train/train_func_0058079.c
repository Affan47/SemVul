exportToImage()
{

	QString fileName = QFileDialog::getSaveFileName(this, tr("Export to Image"), "",
	                       tr("Image files (*.png *.bmp)"));
	if (fileName.isEmpty())
		return;
	if (!fileName.endsWith(".png", Qt::CaseInsensitive) &&
	    !fileName.endsWith(".bmp", Qt::CaseInsensitive))
			fileName += ".png";

	createPixmap().save(fileName);
}
