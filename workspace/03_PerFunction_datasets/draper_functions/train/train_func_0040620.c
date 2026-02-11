show_style_ellipse()
{
    SHOW_ALL_NL;
    fprintf(stderr, "\tEllipse style has default size ");
    show_position(&default_ellipse.o.ellipse.extent);
    fprintf(stderr, ", default angle is %.1f degrees", default_ellipse.o.ellipse.orientation);

    switch (default_ellipse.o.ellipse.type) {
        case ELLIPSEAXES_XY:
            fputs(", diameters are in different units (major: x axis, minor: y axis)\n", stderr);
	    break;
	case ELLIPSEAXES_XX:
	    fputs(", both diameters are in the same units as the x axis\n", stderr);
	    break;
	case ELLIPSEAXES_YY:
	    fputs(", both diameters are in the same units as the y axis\n", stderr);
	    break;
    }
}
