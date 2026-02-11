calculate_item_sizes(MenuSizingParameters *msp)
{
	MenuItem *mi;
	MenuItemPartSizesT mipst;
	int i;
	Bool do_reverse_icon_order =
		(MST_USE_LEFT_SUBMENUS(msp->menu)) ? True : False;

	memset(&(msp->max), 0, sizeof(msp->max));

	for (mi = MR_FIRST_ITEM(msp->menu); mi != NULL; mi = MI_NEXT_ITEM(mi))
	{
		if (MI_IS_TITLE(mi))
		{
			menuitem_get_size(
				mi, &mipst, MST_PTITLEFONT(msp->menu),
				do_reverse_icon_order);
		}
		else
		{
			menuitem_get_size(
				mi, &mipst, MST_PSTDFONT(msp->menu),
				do_reverse_icon_order);
		}

		if (msp->max.i.triangle_width < mipst.triangle_width)
		{
			msp->max.i.triangle_width = mipst.triangle_width;
		}
		if (msp->max.i.title_width < mipst.title_width)
		{
			msp->max.i.title_width = mipst.title_width;
		}
		for (i = 0; i < MAX_MENU_ITEM_LABELS; i++)
		{
			if (msp->max.i.label_width[i] < mipst.label_width[i])
			{
				msp->max.i.label_width[i] =
					mipst.label_width[i];
			}
		}
		if (msp->max.i.picture_width < mipst.picture_width)
		{
			msp->max.i.picture_width = mipst.picture_width;
		}
		for (i = 0; i < MAX_MENU_ITEM_MINI_ICONS; i++)
		{
			if (msp->max.i.icon_width[i] < mipst.icon_width[i])
			{
				msp->max.i.icon_width[i] = mipst.icon_width[i];
			}
		}
	}
	if (MR_SIDEPIC(msp->menu))
	{
		msp->max.sidepic_width = MR_SIDEPIC(msp->menu)->width;
	}
	else if (MST_SIDEPIC(msp->menu))
	{
		msp->max.sidepic_width = MST_SIDEPIC(msp->menu)->width;
	}

	return;
}
