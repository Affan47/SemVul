slideDragImage(PG_Point start, PG_Point end, int steps, SDL_Surface* image) {
	double dx, dy;
	PG_Point current,old;

	dx = end.x - start.x;
	dy = end.y - start.y;

	dx /= steps;
	dy /= steps;

	for(int i=0; i<steps; i++) {
		current.x = (int)((double)start.x + (double)i*dx);
		current.y = (int)((double)start.y + (double)i*dy);

		if(i>0) {
			drawDragArea(old, dragimagecache);
		}

		cacheDragArea(current);
		drawDragArea(current, dragimage);
		updateDragArea(current, dragimage);

		if(i>0) {
			updateDragArea(old, dragimagecache);
		}

		old = current;

		SDL_Delay(10);
	}

	drawDragArea(old, dragimagecache);
	updateDragArea(old, dragimagecache);
}
