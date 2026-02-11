setPressedImage(video::ITexture* image)
{
	if (image)
		image->grab();

	if (PressedImage)
		PressedImage->drop();

	PressedImage = image;
	if (image)
		PressedImageRect = core::rect<s32>(core::position2d<s32>(0,0), image->getOriginalSize());
}
