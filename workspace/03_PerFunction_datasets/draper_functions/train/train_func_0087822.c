uih_setguessing(uih_context * c, int range)
{
    char str[10];
    c->fcontext->range = range;
    if (range <= 1) {
	uih_updatemenus(c, "noguess");
    } else if (range > 8) {
	uih_updatemenus(c, "guessall");
    } else {
	sprintf(str, "guess%i", range);
	uih_updatemenus(c, str);
    }
}
