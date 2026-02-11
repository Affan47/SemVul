PG_Slider(PG_Widget* parent, const PG_Rect& r, ScrollDirection direction, int id, const std::string& style) : PG_ScrollBar(parent, r, direction, id) {
	delete scrollbutton[0];
	scrollbutton[0] = NULL;

	delete scrollbutton[1];
	scrollbutton[1] = NULL;


	sigScrollPos.connect(sigSlideEnd.slot());
	sigScrollTrack.connect(sigSlide.slot());

	LoadThemeStyle(style);
	SetPosition(scroll_min);
}
