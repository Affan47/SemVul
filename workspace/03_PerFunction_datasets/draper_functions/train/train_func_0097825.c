setImage(const QImage& i)
{
	if (i.width() > MAX_AVATAR_DISPLAY_SIZE || i.height() > MAX_AVATAR_DISPLAY_SIZE)
		pixmap_.convertFromImage(i.scaled(MAX_AVATAR_DISPLAY_SIZE,MAX_AVATAR_DISPLAY_SIZE,Qt::KeepAspectRatio,Qt::SmoothTransformation));
	else
		pixmap_.convertFromImage(i);

}
