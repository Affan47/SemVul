SetSizeByText(int Width, int Height, const std::string& Text) {
	Width += 2 * (*_mid)[UNPRESSED].bordersize + _mid->pressShift;

	SDL_Surface* srf = (*_mid)[UNPRESSED].srf_icon;

	if (srf == NULL) {
		PG_Widget::SetSizeByText(Width, Height, Text);
		eventSizeWidget(my_width, my_height);
		return;
	}

	Uint16 w,h;
	int baselineY;

	if(Text.empty()) {
		if (!PG_FontEngine::GetTextSize(my_text, GetFont(), &w, &h, &baselineY)) {
			return;
		}
	} else {
		PG_String ytext = Text;
		if (!PG_FontEngine::GetTextSize(ytext, GetFont(), &w, &h, &baselineY)) {
			return;
		}
	}

	Uint16 dx = srf->w + Width;

	my_width = (srf->w > w) ? dx : w + dx;
	my_height = PG_MAX(srf->h, h + baselineY) + Height;

	eventSizeWidget(my_width, my_height);
}
