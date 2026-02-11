get_color_by_name(const char *name, const char *fallback)
{
    XColor xcol;

    if (!name) {
        if (!fallback) {
            return ((Pixel) - 1);
        } else {
            name = fallback;
        }
    } else if (isdigit(*name)) {
        unsigned long c;

        c = strtoul(name, (char **) NULL, 0);
        if (c <= 15) {
            name = rs_color[c + minColor];
        }
    }
    if (!XParseColor(Xdisplay, cmap, name, &xcol)) {
        libast_print_warning("Unable to resolve \"%s\" as a color name.  Falling back on \"%s\".\n", name, NONULL(fallback));
        name = fallback;
        if (name) {
            if (!XParseColor(Xdisplay, cmap, name, &xcol)) {
                libast_print_warning
                    ("Unable to resolve \"%s\" as a color name.  This should never fail.  Please repair/restore your RGB database.\n",
                     name);
                return ((Pixel) - 1);
            }
        } else {
            return ((Pixel) - 1);
        }
    }
    if (!XAllocColor(Xdisplay, cmap, &xcol)) {
        libast_print_warning("Unable to allocate \"%s\" (0x%08x:  0x%04x, 0x%04x, 0x%04x) in the color map.  Falling back on \"%s\".\n",
                      name, xcol.pixel, xcol.red, xcol.green, xcol.blue, NONULL(fallback));
        name = fallback;
        if (name) {
            if (!XAllocColor(Xdisplay, cmap, &xcol)) {
                libast_print_warning("Unable to allocate \"%s\" (0x%08x:  0x%04x, 0x%04x, 0x%04x) in the color map.\n", name, xcol.pixel,
                              xcol.red, xcol.green, xcol.blue);
                return ((Pixel) - 1);
            }
        } else {
            return ((Pixel) - 1);
        }
    }
    return (xcol.pixel);
}
