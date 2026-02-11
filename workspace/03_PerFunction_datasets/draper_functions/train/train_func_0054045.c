find_color(RGB rgb)
{
    int i;
    int cindex = BAD_COLOR;

    for (i = 0; i < maxcolors; i++) {
        if (compare_rgb(&cmap_table[i].rgb, &rgb) == TRUE) {
            cindex = i;
            break;
        }
    }

    return (cindex);
}
