fb_drawprogressbar(unsigned percent)
{
	int i, left_x, top_y, width, height;


	left_x = G.nbar_posx;
	top_y = G.nbar_posy;
	width = G.nbar_width - 1;
	height = G.nbar_height - 1;
	if ((height | width) < 0)
		return;

	fb_drawrectangle();


	left_x++;
	top_y++;
	width -= 2;
	height -= 2;
	if ((height | width) < 0)
		return;
	fb_drawfullrectangle(
			left_x,	top_y,
					left_x + width, top_y + height,
			G.nbar_colr, G.nbar_colg, G.nbar_colb);

	if (percent > 0) {

		width = width * percent / 100;
		i = height;
		if (height == 0)
			height++;
		while (i >= 0) {


			unsigned gray_level = 100 + i*100/height;
			fb_drawfullrectangle(
					left_x, top_y, left_x + width, top_y,
					gray_level, gray_level, gray_level);
			top_y++;
			i--;
		}
	}
}
