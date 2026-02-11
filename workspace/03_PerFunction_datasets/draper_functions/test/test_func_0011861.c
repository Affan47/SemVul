calc_scaling(int font_width, int font_height) {
    double font_x_scale = abs(font_width) / (double) XFIG_DEFAULT_FONT_WIDTH;
    double font_y_scale = abs(font_height) / (double) XFIG_DEFAULT_FONT_HEIGHT;

    font_scale = font_x_scale>font_y_scale ? font_x_scale : font_y_scale;
    dpi_scale  = font_scale;
}
