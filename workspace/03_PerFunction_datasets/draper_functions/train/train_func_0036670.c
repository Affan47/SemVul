DestroyAllButtons(FvwmDecor *decor)
{
	TitleButton *tbp;
	DecorFace *face;
	int i;
	int j;

	for (tbp = decor->buttons, i = 0; i < NUMBER_OF_TITLE_BUTTONS;
	     i++, tbp++)
	{
		for (j = 0, face = TB_STATE(*tbp); j < BS_MaxButtonState;
		     j++, face++)
		{
			FreeDecorFace(dpy, face);
		}
	}

	return;
}
