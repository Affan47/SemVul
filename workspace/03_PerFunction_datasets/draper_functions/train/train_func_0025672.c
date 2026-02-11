eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {

	PG_ThemeWidget::eventBlit(srf, src, dst);

	PG_Rect client(0, my_heightTitlebar, my_width, my_height-my_heightTitlebar);
	DrawBorder(client, my_bordersize);

	client.my_xpos++;
	client.my_ypos++;
	client.my_width -= 2;
	client.my_height -= 2;

	DrawBorder(client, my_bordersize, false);
}
