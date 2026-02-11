setGrayPalette(QImage& image)
{
	if (grayTable.isEmpty()) {
		grayTable.resize(256);

		for (int i = 0; i < 256; i++)
			grayTable[i] = qRgb(i, i, i);
	}

	image.setColorTable(grayTable);
}
