mga_hide_cursor(struct mga_device *mdev)
{
	WREG8(MGA_CURPOSXL, 0);
	WREG8(MGA_CURPOSXH, 0);
	if (mdev->cursor.pixels_1->pin_count)
		mgag200_bo_unpin(mdev->cursor.pixels_1);
	if (mdev->cursor.pixels_2->pin_count)
		mgag200_bo_unpin(mdev->cursor.pixels_2);
}
