buttonBGColorset(button_info *b)
{
	if (b->flags.b_Hangon)
	{
		if (b->flags.b_PressColorset)
			return b->pressColorset;
		if (UberButton->c->flags.b_PressColorset &&
			(buttonSwallow(b) & b_UseOld))
		{
			return UberButton->c->pressColorset;
		}
	}
	else if (b == ActiveButton && b->flags.b_ActiveColorset)
		return b->activeColorset;
	else if (b == ActiveButton && UberButton->c->flags.b_ActiveColorset)
		return UberButton->c->activeColorset;
	else if (b == CurrentButton && b->flags.b_PressColorset)
		return b->pressColorset;
	else if (b == CurrentButton && UberButton->c->flags.b_PressColorset)
		return UberButton->c->pressColorset;

	if (b->flags.b_Colorset)
		return b->colorset;

	return -1;
}
