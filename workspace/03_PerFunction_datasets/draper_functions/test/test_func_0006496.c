scale(int width, int height)
{
	image = image.scaled(width, height, Qt::IgnoreAspectRatio,
			     Qt::SmoothTransformation);
	widget()->resize(width, height);
	widget()->update(0, 0, width, height);
	emit sizeUpdated(width,height);
	emit newImage();
}
