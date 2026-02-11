setPreviewPhoto(const QString& path)
{
	QFile photo_file(path);
	if (!photo_file.open(QIODevice::ReadOnly))
		return;

	QByteArray photo_data = photo_file.readAll();
	QImage photo_image(photo_data);
	if(!photo_image.isNull()) {
		d->photo = photo_data;
		updatePhoto();
		d->te_edited = true;
	}
}
