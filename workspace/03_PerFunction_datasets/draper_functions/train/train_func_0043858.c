variantForImage(const QImage &_image)
{
	qDBusRegisterMetaType<SpecImage>();

	QImage image = _image.convertToFormat(QImage::Format_ARGB32);

	int rowStride = image.width() * 4;


	QByteArray data;
	data.resize(rowStride * image.height());
	char* dst = data.data();
	for (int y=0; y<image.height(); ++y) {
		QRgb* src = (QRgb*)image.scanLine(y);
		QRgb* end = src + image.width();
		for (;src != end; ++src) {

			*dst++ = qRed(*src);
			*dst++ = qGreen(*src);
			*dst++ = qBlue(*src);
			*dst++ = qAlpha(*src);
		}
	}

	SpecImage specImage;
	specImage.width = image.width();
	specImage.height = image.height();
	specImage.rowStride = rowStride;
	specImage.hasAlpha = true;
	specImage.bitsPerSample = 8;
	specImage.channels = 4;
	specImage.data = data;

	return QVariant::fromValue(specImage);
}

}
