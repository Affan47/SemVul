setPicture(gPicture *picture)
{
	GdkPixbuf *buf;

	gPicture::assign(&_picture, picture);

	buf = _picture ? _picture->getPixbuf() : NULL;

	if (!buf)
		gtk_widget_hide(image);
	else
	{
		gtk_image_set_from_pixbuf(GTK_IMAGE(image), buf);
		gtk_widget_show(image);
	}
}
