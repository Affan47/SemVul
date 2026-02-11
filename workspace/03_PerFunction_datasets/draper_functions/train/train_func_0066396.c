createPoints(struct state *st)
{
    int    q;
    XPoint *pa = st->aCurr, *pa1 = st->aFrom, *pa2 = st->aTo;
    XPoint *qa1 = st->aSlopeFrom, *qa2 = st->aSlopeTo;
    float  fg, f1g;
    float  speed;

    fg  = st->currGamma;
    f1g = 1.0 - st->currGamma;
    for (q = st->numPoints; q; q--) {
        speed = 0.45 * sin(TWO_PI * (double) (q + st->shift) / (st->numPoints - 1));
        fg = st->currGamma + 1.67 * speed
            * exp(-200.0 * (st->currGamma - 0.5 + 0.7 * speed)
                  * (st->currGamma - 0.5 + 0.7 * speed));

        f1g = 1.0 - fg;
        pa->x = (short) (f1g * f1g * f1g * pa1->x + f1g * f1g * fg
                         * (3 * pa1->x + qa1->x) + f1g * fg * fg
                         * (3 * pa2->x - qa2->x) + fg * fg * fg * pa2->x);
        pa->y = (short) (f1g * f1g * f1g * pa1->y + f1g * f1g * fg
                         * (3 * pa1->y + qa1->y) + f1g * fg * fg
                         * (3 * pa2->y - qa2->y) + fg * fg * fg * pa2->y);

        ++pa;
        ++pa1;
        ++pa2;
	++qa1;
	++qa2;
    }
}
