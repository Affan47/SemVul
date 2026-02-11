MFBDefineColor(colorID, red, green, blue)

int colorID;
int red, green, blue;


{
    XColor mycolor;

    if (!mfb_vltBool)
        return MFBNODFCO;
    if (colorID > mfb_maxColors || colorID < 0)
        return MFBBADCST;
    if (red > 1000 || green > 1000 || blue > 1000)
        return MFBBADCST;

    mycolor.red   = (red   * 65535) / 1000;
    mycolor.green = (green * 65535) / 1000;
    mycolor.blue  = (blue  * 65535) / 1000;
    if (MFBCurrent->privateColors) {
        mycolor.flags = -1;
        mycolor.pixel = mfb_colors[colorID];
        XStoreColor(mfb_display, mfb_cmap, &mycolor);
    }
    else {
        if (mfb_colors[colorID] > -1)
            XFreeColors(mfb_display, mfb_cmap, &mfb_colors[colorID], 1, 0);
        if (!XAllocColor(mfb_display, mfb_cmap, &mycolor))
            return MFBBADCST;
        mfb_colors[colorID] = mycolor.pixel;
    }
    if (mfb_lineGC == mfb_dragGC)
        return (MFBOK);
    MFBSetColor(colorID);
    if (colorID == 0) {
        XSetWindowBackground(mfb_display, mfb_window, mycolor.pixel);
        XSetBackground(mfb_display, mfb_lineGC, mycolor.pixel);
        XSetBackground(mfb_display, mfb_fillGC, mycolor.pixel);
        XSetBackground(mfb_display, mfb_dragGC, mycolor.pixel);
        XSetForeground(mfb_display, mfb_dragGC,
            mycolor.pixel ^ WhitePixel(mfb_display,DefaultScreen(mfb_display)));
    }
    return MFBOK;
}
