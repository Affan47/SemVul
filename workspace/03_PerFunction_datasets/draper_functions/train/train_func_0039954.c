GB_COLOR_from_format(uint col, int format)
{
	if (GB_IMAGE_FMT_IS_RGBA(format))
		col = SWAP_RED_BLUE(col);
	if (GB_IMAGE_FMT_IS_SWAPPED(format))
		col = SWAP(col);
	if (GB_IMAGE_FMT_IS_PREMULTIPLIED(format))
		col = INV_PREMUL(col);
	return col ^ 0xFF000000;
}
