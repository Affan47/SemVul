write_gnuplot_font_string (char *fstr, PlotType ptype, int pngterm,
			   const char *grfont, double scale)
{
    if (grfont == NULL) {
	grfont = gretl_png_font();
    }

    if (*grfont == '\0') {
	grfont = getenv("GRETL_PNG_GRAPH_FONT");
    }

    if (grfont == NULL || *grfont == '\0') {
	*fstr = '\0';
	return;
    }

    if (pngterm == GP_PNG_CAIRO) {
	char fname[128];
	int nf, fsize = 0;

	nf = split_graph_fontspec(grfont, fname, &fsize);
	if (nf == 2) {
	    if (maybe_big_multiplot(ptype) && gp_small_font_size > 0) {
		fsize = gp_small_font_size;
	    }
	    if (scale > 1.0) {
		fsize = round(scale * fsize);
	    }
	    sprintf(fstr, " font \"%s,%d\"", fname, fsize);
	} else if (nf == 1) {
	    sprintf(fstr, " font \"%s\"", fname);
	}
    } else {
	int shrink = 0;

	if (maybe_big_multiplot(ptype) && gp_small_font_size > 0) {
	    char fname[64];
	    int fsize;

	    if (sscanf(grfont, "%s %d", fname, &fsize) == 2) {
		sprintf(fstr, " font %s %d", fname, gp_small_font_size);
		shrink = 1;
	    }
	}

	if (!shrink) {
	    sprintf(fstr, " font %s", grfont);
	}
    }
}
