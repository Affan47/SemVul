DrawLine(SDL_Surface* surface, Uint32 x0, Uint32 y0, Uint32 x1, Uint32 y1, const PG_Color& color, Uint8 width) {
	int deltax;
	int deltay;
	int temp;
	int pixelflag;

	if (!width || !surface)
		return;

   SDL_LockSurface(surface);

	pixelflag=0;


	if (y0 > y1) {
		temp = y0;
		y0 = y1;
		y1 = temp;
		temp = x0;
		x0 = x1;
		x1 = temp;

	}


	deltax = x1 - x0;
	deltay = y1 - y0;
	if (deltax > 0) {
		if (deltax > deltay) {
			octant0(surface, x0, y0, deltax, deltay, 1, color, width, pixelflag);
		}
		else {
			octant1(surface, x0, y0, deltax, deltay, 1, color, width, pixelflag);
		}

	}
	else {
		deltax = -deltax;
		if (deltax > deltay) {
			octant0(surface, x0, y0, deltax, deltay, -1, color, width, pixelflag);
		}
		else {

			octant1(surface, x0, y0, deltax, deltay, -1, color, width, pixelflag);
		}
	}

   SDL_UnlockSurface(surface);

}
