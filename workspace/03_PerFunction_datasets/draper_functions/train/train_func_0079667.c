setFromString(const char *color_string, int screen) {

    if (color_string == 0) {
        free();
        return false;
    }
    string color_string_tmp = color_string;
    StringUtil::removeFirstWhitespace(color_string_tmp);
    StringUtil::removeTrailingWhitespace(color_string_tmp);

    Display *disp = App::instance()->display();
    Colormap colm = DefaultColormap(disp, screen);

    XColor color;

    if (! XParseColor(disp, colm, color_string_tmp.c_str(), &color))
        return false;
    else if (! XAllocColor(disp, colm, &color))
        return false;

    setPixel(color.pixel);
    setRGB(maxValue(color.red),
           maxValue(color.green),
           maxValue(color.blue));
    setAllocated(true);
    m_screen = screen;

    return true;
}
