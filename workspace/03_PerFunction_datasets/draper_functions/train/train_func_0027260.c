clear_icon(FvwmWindow *fw)
{
	FW_W_ICON_PIXMAP(fw) = None;
	fw->iconPixmap = None;
	fw->icon_maskPixmap = None;
	fw->icon_alphaPixmap = None;
	fw->icon_nalloc_pixels = 0;
	fw->icon_alloc_pixels = NULL;
	fw->icon_no_limit = 0;
	if (IS_ICON_MOVED(fw))
	{
		clear_icon_dimensions(fw);
	}
	else
	{
		memset(&fw->icon_g, 0, sizeof(fw->icon_g));
	}

	return;
}
