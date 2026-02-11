setIconInternal(NETRArray<NETIcon>& icons, int& icon_count, Atom property, NETIcon icon, Bool replace) {
    if (p->role != Client) return;

    int proplen, i, sz, j;

    if (replace) {

	for (i = 0; i < icons.size(); i++) {
	    delete [] icons[i].data;
	    icons[i].data = 0;
	    icons[i].size.width = 0;
	    icons[i].size.height = 0;
	}

	icon_count = 0;
    }


    icons[icon_count] = icon;
    icon_count++;


    NETIcon &ni = icons[icon_count - 1];
    sz = ni.size.width * ni.size.height;
    CARD32 *d = new CARD32[sz];
    ni.data = (unsigned char *) d;
    memcpy(d, icon.data, sz * sizeof(CARD32));


    for (i = 0, proplen = 0; i < icon_count; i++) {
	proplen += 2 + (icons[i].size.width *
			icons[i].size.height);
    }

    CARD32 *d32;
    long *prop = new long[proplen], *pprop = prop;
    for (i = 0; i < icon_count; i++) {

       	*pprop++ = icons[i].size.width;
	*pprop++ = icons[i].size.height;


	sz = (icons[i].size.width * icons[i].size.height);
	d32 = (CARD32 *) icons[i].data;
	for (j = 0; j < sz; j++) *pprop++ = *d32++;
    }

    XChangeProperty(p->display, p->window, property, XA_CARDINAL, 32,
		    PropModeReplace, (unsigned char *) prop, proplen);

    delete [] prop;
    delete [] p->icon_sizes;
    p->icon_sizes = NULL;
}
