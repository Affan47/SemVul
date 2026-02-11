set_color(const char *name, const char *mapset, const char *color,
		     struct Ref *ref)
{
    int n;

    for (n = 0; n < ref->nfiles; n++) {
	if (strcmp(ref->file[n].name, name) == 0
	    && strcmp(ref->file[n].mapset, mapset) == 0)
	    break;
    }

    if (n < ref->nfiles)
	while (*color) {
	    switch (*color) {
	    case 'r':
	    case 'R':
		if (ref->red.n < 0)
		    ref->red.n = n;
		break;
	    case 'g':
	    case 'G':
		if (ref->grn.n < 0)
		    ref->grn.n = n;
		break;
	    case 'b':
	    case 'B':
		if (ref->blu.n < 0)
		    ref->blu.n = n;
		break;
	    }
	    color++;
	}

    return 0;
}
