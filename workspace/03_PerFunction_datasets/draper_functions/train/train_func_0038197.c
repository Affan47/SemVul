eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {

	if((dst.my_width == 0) || (dst.my_height == 0)) {
		return;
	}

	if(my_srfHover == NULL) {
		my_srfHover = PG_ThemeWidget::CreateThemedSurface(
		                  PG_Rect(0, 0, my_width, my_height),
		                  my_gradient[2],
		                  my_background[2],
		                  my_bkmode[2],
		                  my_blend[2]);
	}

	if(my_srfSelected == NULL) {
		my_srfSelected = PG_ThemeWidget::CreateThemedSurface(
		                     PG_Rect(0, 0, my_width, my_height),
		                     my_gradient[1],
		                     my_background[1],
		                     my_bkmode[1],
		                     my_blend[1]);
	}

	if(my_selected) {
		PG_Widget::eventBlit(my_srfSelected, src, dst);
	} else if(my_hover) {
		PG_Widget::eventBlit(my_srfHover, src, dst);
	}

	PG_Label::eventBlit(NULL, src, dst);
}
