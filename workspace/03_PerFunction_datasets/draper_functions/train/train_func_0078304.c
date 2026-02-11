mouse_cursor_is_on_that_image(float pos_x, float pos_y, struct image *our_image)
{

	SDL_Rect screen_rectangle;

	screen_rectangle.x = translate_map_point_to_screen_pixel_x(pos_x, pos_y) + our_image->offset_x;
	screen_rectangle.y = translate_map_point_to_screen_pixel_y(pos_x, pos_y) + our_image->offset_y;
	screen_rectangle.w = our_image->w;
	screen_rectangle.h = our_image->h;

	if (MouseCursorIsInRect(&(screen_rectangle),
				input_axis.x + User_Rect.w / 2 + User_Rect.x, input_axis.y + User_Rect.h / 2 + User_Rect.y)) {
		return (TRUE);
	}

	return (FALSE);
}
