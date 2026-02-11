read_line(double e1, double n1, double e2, double n2)
{
    char buf[300];
    int r, g, b;
    int color_R, color_G, color_B;
    int ret;
    double width;
    int masked;
    char ch, *key, *data;

    static char *help[] = {
	"color  color",
	"width  #",
	"masked [y|n]",
	""
    };

    width = 1.;
    color_R = color_G = color_B = 0;
    masked = 0;

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

	if (KEY("width")) {
	    ch = ' ';
	    if (sscanf(data, "%lf%c", &width, &ch) < 1 || width < 0.) {
		width = 1.;
		error(key, data, "illegal width request");
	    }
	    if (ch == 'i')
		width = width * 72.;
	    continue;
	}

	error(key, data, "illegal line request");
    }

    sprintf(buf, "L %d %f %f %f %f %d %d %d %.8f",
	    masked, e1, n1, e2, n2, color_R, color_G, color_B, width);

    add_to_plfile(buf);

    return 0;
}
