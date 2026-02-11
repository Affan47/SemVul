GMT_img_setup_coord (struct GMT_IMG_RANGE *r, struct GMT_IMG_COORD *c)
{


	if (r->maxlon < 360.0) {
		fprintf (stderr, "ERROR from GMT_img_setup_coord:  Cannot handle maxlon < 360.\n");
		return (-1);
	}

	c->nxcol  = (GMT_LONG)irint (r->maxlon * 60.0 / r->mpixel);
	c->nx360  = (GMT_LONG)irint (360.0 * 60.0 / r->mpixel);
	c->radius = c->nx360 / (2.0 * M_PI);
	c->nytop  = (GMT_LONG)irint (c->radius * GMT_img_gud_inv(r->maxlat*D2R) );
	c->nyrow  = c->nytop - (GMT_LONG)irint (c->radius * GMT_img_gud_inv(r->minlat*D2R) );

	return (0);
}
