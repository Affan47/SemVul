makeIcon()
{
	if ( !icon_ )
		return QPixmap();

#ifdef Q_WS_X11

	QImage real(22,22,32);
	QImage in = icon_->image();
	in.detach();
	real.setAlphaBuffer(true);


	if(in.width() > 16 || in.height() > 16)
		in = in.smoothScale(16,16);

	int xo = (real.width() - in.width()) / 2;
	int yo = (real.height() - in.height()) / 2;

	int n, n2;


	for(n2 = 0; n2 < real.height(); ++n2)
		for(n = 0; n < real.width(); ++n)
			real.setPixel(n, n2, qRgba(0,0,0,0));


	for(n2 = 0; n2 < in.height(); ++n2) {
		for(n = 0; n < in.width(); ++n) {
			if(int a = qAlpha(in.pixel(n,n2))) {
				int x = n + xo + 2;
				int y = n2 + yo + 2;
				real.setPixel(x, y, qRgba(0x80,0x80,0x80,a));
			}
		}
	}


	for(n2 = 0; n2 < in.height(); ++n2) {
		for(n = 0; n < in.width(); ++n) {
			if(qAlpha(in.pixel(n,n2))) {
				QRgb pold = real.pixel(n + xo , n2 + yo);
				QRgb pnew = in.pixel(n , n2);
				real.setPixel(n + xo, n2 + yo, pixelBlend(pold, pnew));
			}
		}
	}

	QPixmap pixmap;
	pixmap.convertFromImage(real);
	return pixmap;
#else
	return icon_->pixmap();
#endif
}
