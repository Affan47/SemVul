take_image(CIMAGE *_object, gPicture *image)
{
	IMAGE.Take(&THIS->img, &_image_owner, image, image->width(), image->height(), image->data());

	if (!image->getTag())
		image->setTag(new gGambasTag(THIS));
}
