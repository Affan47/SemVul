init_items (void)
{
  int i, j;
  a_pcx_image trailimg, arrow_img;

  big_dollar = compile_sprshade (IMGPOS (main_font_img, 81, 0),
				 0, 1, glenz[0],
				 17, 17, main_font_img.width, xbuf);
  small_dollar = compile_sprshade (IMGPOS (main_font_img, 81, 18),
				   0, 1, glenz[0],
				   10, 10, main_font_img.width, xbuf);
  for (i = 0; i < NBR_CLOCK_FRAMES; ++i)
    clocks[i] = compile_sprshade (IMGPOS (main_font_img, 81, 52 + i * 10),
				  0, 1, glenz[0],
				  10, 10, main_font_img.width, xbuf);
  for (i = 0; i < NBR_PYRAMIDS; ++i)
    pyramids[i] = compile_sprshade (IMGPOS (main_font_img, 64, i * 16),
				    0, 1, glenz[0],
				    7, 9, main_font_img.width, xbuf);

  pcx_load_from_rsc ("arrow-img", &arrow_img);
  for (i = 0; i < 3; ++i)
    for (j = 0; j < 4; ++j)
      tutorial_arrow[i * 4 + j] =
	compile_sprunish (IMGPOS (arrow_img, i * 26, j * 26),
			  0, 200, glenz[0], 10, 26, 26, arrow_img.width, xbuf);
  img_free (&arrow_img);

  pcx_load_from_rsc ("trails-img", &trailimg);
  for (i = 0; i < 16; ++i) {
    if (trail_row[i] < 0)
      for (j = 0 ; j < 12; ++j)
	trails[i][j] = 0;
    else
      for (j = 0 ; j < 12; ++j)
	trails[i][j] = compile_sprglenz (IMGPOS (trailimg,
						 trail_row[i], j << 4),
					 0, glenz[0],
					 10, 12, trailimg.width, xbuf);
  }
  for (i = 0; i < 4; ++i)
    red_cross[i] = compile_sprglenz (IMGPOS (main_font_img, 119, i << 6),
				     0, glenz[6],
				     22, 40, main_font_img.width, xbuf);
  img_free (&trailimg);
}
