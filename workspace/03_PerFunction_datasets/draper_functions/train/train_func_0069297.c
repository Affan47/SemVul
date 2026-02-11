GMT_putwords (double x, double y, char **text, GMT_LONG n_words, struct PSTEXT_INFO *T) {
	char *boxpen_texture = CNULL, *vecpen_texture = CNULL;
	GMT_LONG boxpen_width, boxpen_offset, vecpen_width, vecpen_offset, i;
	int boxpen_rgb[3], vecpen_rgb[3];
	double dx, dy;

	boxpen_texture = GMT_convertpen (&T->boxpen, &boxpen_width, &boxpen_offset, boxpen_rgb);
	vecpen_texture = GMT_convertpen (&T->vecpen, &vecpen_width, &vecpen_offset, vecpen_rgb);

	if (T->space_flag) {
		dx = 0.01 * T->x_space * T->font_size / 72.0;
		dy = 0.01 * T->y_space * T->font_size / 72.0;
	}
	else {
		dx = T->x_space;
		dy = T->y_space;
	}
	ps_words (x, y, text, n_words, T->line_spacing, T->paragraph_width, T->text_justify, T->paragraph_font, T->font_size,
		T->paragraph_angle, T->txtfill.rgb, T->block_justify, T->boxflag, T->x_offset, T->y_offset, dx, dy,
		boxpen_width, boxpen_texture, boxpen_offset, boxpen_rgb,
		vecpen_width, vecpen_texture, vecpen_offset, vecpen_rgb,
		T->boxfill.rgb);

	if (boxpen_texture) GMT_free ((void *)boxpen_texture);
	if (vecpen_texture) GMT_free ((void *)vecpen_texture);

	for (i = 0; i < n_words; i++) free ((void *)text[i]);
}
