mkrgb(struct palette *c)
{
    int ncolors = c->size;
    int red = 8, green = 8, blue = 4;

    context = c;
    needupdate = 0;

    if (c->flags & UNKNOWNENTRIES) {
	while (blue > 0) {
	    if (allocrgb(c, red, green, blue))
		break;
	    red--;
	    if (allocrgb(c, red, green, blue))
		break;
	    green--;
	    if (allocrgb(c, red, green, blue))
		break;
	    red--;
	    if (allocrgb(c, red, green, blue))
		break;
	    green--;
	    if (allocrgb(c, red, green, blue))
		break;
	    blue--;
	}
    } else {
	number_t n =
	    pow((c->maxentries - nprecells) / (0.5 * 0.2 * 0.3), 1.0 / 3);
	green = (int) (n * 0.5);
	blue = (int) (n * 0.2);
	red = (int) (n * 0.3);
	while ((blue + 1) * red * green < (c->maxentries - nprecells))
	    blue++;
	while ((red + 1) * blue * green < (c->maxentries - nprecells))
	    red++;
	while ((green + 1) * blue * red < (c->maxentries - nprecells))
	    green++;
	allocrgb(c, red, green, blue);
    }

    if (!(c->flags & FINISHLATER)) {
	if (c->allocfinished != NULL)
	    c->allocfinished(c);
    } else
	c->flags |= UNFINISHED;
    if (context->size != ncolors || needupdate) {
	context->version++;
    }

    return red * 256 * 256 + green * 256 + blue;
}
