trace_line(const anwcs_t* wcs, const dl* rd,
                      int istart, int idir, int iend,
					  anbool firstmove, dl* plotrd) {
	int i;
	double lastra=0, lastdec=0;
	double first = TRUE;
    logverb("trace_line: %i to %i by %i\n", istart, iend, idir);
	for (i = istart; i != iend; i += idir) {
		double x,y,ra,dec;
		ra  = dl_get_const(rd, 2*i+0);
		dec = dl_get_const(rd, 2*i+1);
		logverb("tracing: i=%i, ra,dec = %g,%g\n", i, ra, dec);
		if (anwcs_radec2pixelxy(wcs, ra, dec, &x, &y))

			continue;
		if (first) {
            logdebug("plot to (%.2f, %.2f)\n", ra, dec);
            dl_append(plotrd, x);
            dl_append(plotrd, y);
		} else {
			if (anwcs_is_discontinuous(wcs, lastra, lastdec, ra, dec)) {
                logverb("discont: (%.2f, %.2f) -- (%.2f, %.2f)\n",
                       lastra, lastdec, ra, dec);
                logverb("return %i\n", i);
				return i;
			} else {
                logverb("not discontinuous\n");
            }
            logdebug("plot to (%.2f, %.2f)\n", ra, dec);
            dl_append(plotrd, x);
            dl_append(plotrd, y);
		}
		lastra = ra;
		lastdec = dec;
		first = FALSE;
	}
	return 0;
}
