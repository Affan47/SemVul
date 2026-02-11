MouseCursorIsInRect(const SDL_Rect *our_rect, int x, int y)
{


	if (x > our_rect->x + our_rect->w)
		return (FALSE);
	if (x < our_rect->x)
		return (FALSE);
	if (y > our_rect->y + our_rect->h)
		return (FALSE);
	if (y < our_rect->y)
		return (FALSE);


	return (TRUE);

}
