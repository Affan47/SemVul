flip_buffer (int p2)
{
  int i, y, left, j;
  for (i = 0; i < 200; i++) {
    y = which_line (i - 100, p2);
    if (y >= -100 && y < 100) {
      left = which_offset (y, p2) + 160;
      if (left >= 0) {
	y += 100;
	for (j = 0; j < left; j++)
	  render_buffer[1][i * xbuf + j] = 0;
	horizontal_zoom_wave (corner[0] + y * xbuf,
			      render_buffer[1] + i * xbuf + left, 320,
			      320 - left - left);
	for (j = 320 - left; j < 320; j++)
	  render_buffer[1][i * xbuf + j] = 0;
      } else {
	left = which_column (y, p2) + 160;
	y += 100;
	horizontal_zoom_flip (corner[0] + y * xbuf + left,
			      render_buffer[1] + i * xbuf,
			      320 - left - left, 320);
      }
    } else {
      memset (render_buffer[1] + i * xbuf, 0, 320);
    }
  }
}
