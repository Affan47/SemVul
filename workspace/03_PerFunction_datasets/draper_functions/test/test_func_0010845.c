read_point(double e, double n)
{
    char buf[1024], symb[1024];
    int r, g, b;
    int color_R, color_G, color_B;
    int fcolor_R, fcolor_G, fcolor_B;
    int ret;
    double size, rotate;
    int have_icon;
    char *key, *data;
    int masked;

    static char *help[] = {
	"color  color",
	"fcolor fill color",
	"symbol group/symbol",
	"size   #",
	"rotate #",
	"masked [y|n]",
	""
    };

    size = 6.0;
    rotate = 0.0;
    have_icon = 0;
    masked = 0;
    color_R = color_G = color_B = 0;
    fcolor_R = fcolor_G = fcolor_B = 128;

    while (input(2, buf, help)) {
	if (!key_data(buf, &key, &data))
	    continue;

	if (KEY("masked")) {
	    masked = yesno(key, data);
	    if (masked)
		PS.mask_needed = 1;
	    continue;
	}
	if (KEY("color")) {
	    ret = G_str_to_color(data, &r, &g, &b);
	    if (ret == 1) {
		color_R = r;
		color_G = g;
		color_B = b;
	    }
	    else if (ret == 2)
		color_R = color_G = color_B = -1;
	    else
		error(key, data, "illegal color request");

	    continue;
	}
	if (KEY("fcolor")) {
	    ret = G_str_to_color(data, &r, &g, &b);
	    if (ret == 1) {
		fcolor_R = r;
		fcolor_G = g;
		fcolor_B = b;
	    }
	    else if (ret == 2)
		fcolor_R = fcolor_G = fcolor_B = -1;
	    else
		error(key, data, "illegal color request");

	    continue;
	}
	if (KEY("symbol")) {

	    strcpy(symb, data);
	    continue;
	}

	if (KEY("size")) {
	    if (sscanf(data, "%lf", &size) != 1 || size <= 0.0) {
		size = 1.0;
		error(key, data, "illegal size request");
	    }
	    continue;
	}
	if (KEY("rotate")) {
	    if (sscanf(data, "%lf", &rotate) != 1) {
		rotate = 0.0;
		error(key, data, "illegal rotate request");
	    }
	    continue;
	}

	error(key, data, "illegal point request");
    }

    sprintf(buf, "P %d %f %f %d %d %d %d %d %d %f %f %s", masked, e, n,
	    color_R, color_G, color_B, fcolor_R, fcolor_G, fcolor_B, size,
	    rotate, symb);

    add_to_plfile(buf);

    return 0;
}
