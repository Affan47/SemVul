IwiInitMipmaps(ILimage *BaseImage, ILuint *NumMips)
{
	ILimage	*Image;
	ILuint	Width, Height, Mipmap;

	Image = BaseImage;
	Width = BaseImage->Width;  Height = BaseImage->Height;
	Image->Origin = IL_ORIGIN_UPPER_LEFT;

	for (Mipmap = 0; Width != 1 && Height != 1; Mipmap++) {

		Width = (Width >> 1) == 0 ? 1 : (Width >> 1);
		Height = (Height >> 1) == 0 ? 1 : (Height >> 1);

		Image->Mipmaps = ilNewImageFull(Width, Height, 1, BaseImage->Bpp, BaseImage->Format, BaseImage->Type, NULL);
		if (Image->Mipmaps == NULL)
			return IL_FALSE;
		Image = Image->Mipmaps;


		Image->Format = BaseImage->Format;
		Image->Type = BaseImage->Type;

		Image->Origin = IL_ORIGIN_UPPER_LEFT;
	}

	*NumMips = Mipmap;
	return IL_TRUE;
}
