create(int cols, int rows)
{
	image = QImage(cols, rows, QImage::Format_RGB32);
	image.fill(qRgb(80,80,80));
	widget()->resize(cols, rows);
	widget()->update(0, 0, cols, rows);
	emit sizeUpdated(cols,rows);
	emit newImage();
}
