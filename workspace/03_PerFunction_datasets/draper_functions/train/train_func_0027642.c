PG_ColorBox(PG_ColorSelector* parent, const PG_Rect& r) : PG_ThemeWidget(parent, r) {

	SetBackground((SDL_Surface*)NULL);
	SetSimpleBackground(false);

	my_btndown = false;

	p.x = r.w/2;
	p.y = r.h/2;
}
