colorblind_filter_hue_shift_positive(COLORBLIND_RUNTIME* cbr, COLORBLIND_XCOLOR* color) {
        if (color->red == color->green && color->green == color->blue)
                return 0;
        int a = color->blue;
        color->blue = color->green;
        color->green = color->red;
        color->red = a;
        return 1;
}
