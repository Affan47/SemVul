pixelsCollide(QImage * image1, QImage * image2, int x1, int y1, int x2, int y2) {
	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			QRgb p1 = image1->pixel(x, y);
			if (p1 == 0xffffffff) continue;

			QRgb p2 = image2->pixel(x, y);
			if (p2 == 0xffffffff) continue;


			return true;
		}
	}

	return false;
}
