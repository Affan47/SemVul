iSetImage0()
{
	if (ImageStack == NULL)
		if (!iEnlargeStack())
			return;

	LastUsed = 1;
	CurName = 0;
	ParentImage = IL_TRUE;
	if (!ImageStack[0])
		ImageStack[0] = ilNewImage(1, 1, 1, 1, 1);
	iCurImage = ImageStack[0];
	ilDefaultImage();

	return;
}
