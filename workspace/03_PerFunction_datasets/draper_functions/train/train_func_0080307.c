drawWormhole( struct state *st, wormhole * worm )
{

	int i;
	int color;
	int z;
	starline * current;
	XColor * xcol;
	XColor * shade;

	XSetForeground( st->dpy, st->gc, worm->black.pixel );
	XFillRectangle( st->dpy, worm->work, st->gc, 0, 0, st->SCREEN_X, st->SCREEN_Y );

	for ( i = 0; i < worm->num_stars; i++ )
		if ( worm->stars[i] != NULL ){

			current = worm->stars[i];
			z = current->begin.Z;

			color = z * worm->changer.shade_use / worm->max_Z;
			shade = getColorShade( &worm->changer );

			xcol = &shade[ color ];

			XSetForeground( st->dpy, st->gc, xcol->pixel );

			XDrawLine( st->dpy, worm->work, st->gc, current->begin.calc_x, current->begin.calc_y, current->end.calc_x, current->end.calc_y );

		}
        if (worm->work != st->window)
          XCopyArea( st->dpy, worm->work, st->window, st->gc, 0, 0, st->SCREEN_X, st->SCREEN_Y, 0, 0 );
}
