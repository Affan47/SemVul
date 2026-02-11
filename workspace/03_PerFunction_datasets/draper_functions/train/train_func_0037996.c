initWormhole( struct state *st, wormhole * worm, Display * display, Window win )
{

	int i;
	XWindowAttributes attr;

	XGetWindowAttributes( st->dpy, st->window, &attr );

	st->cmap = attr.colormap;

	st->SCREEN_X = attr.width;
	st->SCREEN_Y = attr.height;

# ifdef HAVE_COCOA
        worm->work = st->window;
# else
	worm->work = XCreatePixmap( st->dpy, st->window, st->SCREEN_X, st->SCREEN_Y, attr.depth );
# endif

	worm->diameter = rnd( 10 ) + 15;
	worm->diameter_change = rnd( 10 ) + 15;


	worm->actualx = attr.width / 2;
	worm->actualy = attr.height / 2;
	worm->virtualx = worm->actualx;
	worm->virtualy = worm->actualy;
	worm->speed = (float)st->SCREEN_X / 180.0;

	worm->spiral = 0;
	worm->addStar = st->make_stars;
	worm->want_x = rnd( attr.width - 50 ) + 25;
	worm->want_y = rnd( attr.height - 50 ) + 25;
	worm->want_ang = gang( worm->actualx, worm->actualy, worm->want_x, worm->want_y );
	worm->ang = worm->want_ang;
	worm->max_Z = 600;
	worm->black.red = 0;
	worm->black.green = 0;
	worm->black.blue = 0;
	XAllocColor( st->dpy, st->cmap, &worm->black );
	initColorChanger( st, &(worm->changer) );

	worm->num_stars = 64;
	worm->stars = (starline **)malloc( sizeof(starline *) * worm->num_stars );
	for ( i = 0; i < worm->num_stars; i++ )
		worm->stars[i] = NULL;

}
