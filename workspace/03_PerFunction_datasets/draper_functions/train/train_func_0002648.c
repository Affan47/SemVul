save_float(struct uih_context *uih, number_t number)
{
    if (!first)
	myputc(' ');
    else
	first = 0;
#ifdef HAVE_LONG_DOUBLE

#ifdef USE_XLDIO
    x_ldout((long double) number, 20, uih->savec->file);
#else
    {
	char s[256];
	sprintf(s, "%.20LG", (long double) number);
	myputs(s);
    }
#endif
#else
    {
	char s[256];
	sprintf(s, "%.20G", (double) number);
	myputs(s);
    }
#endif
}
