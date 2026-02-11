MFBKeyboard(X, Y, background, foreground)

int X, Y;
int background, foreground;


{
    static char InputBuffer[200];
    int key;
    int curX, curY, curLen, ytop, width, x, y, button;
    int cursorwidth;
    Bool fullScreenCursorSave;

    fullScreenCursorSave = mfb_fullScreenCursor;
    MFBSetFullScreenCursor(false);
    X += mfb_fontXOffset;
    Y = TRAN(Y) - mfb_fontYOffset;
    curX = X;
    curY = Y;
    ytop = curY - mfb_font->ascent;
    curLen = 0;
    cursorwidth = XTextWidth(mfb_font, "X", 1);
    XFillRectangle(mfb_display, mfb_window, mfb_dragGC,
                        curX, ytop, cursorwidth, mfb_fontHeight);
    for (;;) {
        MFBPoint(&x, &y, &key, &button);
        if (button == -1) {
            XFillRectangle(mfb_display, mfb_window, mfb_dragGC,
                        curX, ytop, cursorwidth, mfb_fontHeight);
            if (key == CR || key == LF) {
                InputBuffer[curLen] = '\0';
                MFBSetFullScreenCursor(fullScreenCursorSave);
                return InputBuffer;
            }
            else if ((key == BS || key == DEL) && curLen > 0) {

                width = XTextWidth(mfb_font, &InputBuffer[--curLen], 1);
                curX -= width;
                XClearArea(mfb_display, mfb_window, curX, ytop,
                                width, mfb_fontHeight, False);
            }
            else if ((key == CTRLU || key == CTRLX) && curLen > 0) {

                width = curX - X;
                curX = X;
                XClearArea(mfb_display, mfb_window, curX, ytop,
                                width, mfb_fontHeight, False);
                curLen = 0;
            }
            else if (key >= ' ' && key < DEL) {

                char c = key;
                InputBuffer[curLen++] = c;
                XDrawImageString(mfb_display, mfb_window,
                                mfb_lineGC, curX, curY, &c, 1);
                curX += XTextWidth(mfb_font, &c, 1);
            }
            XFillRectangle(mfb_display, mfb_window, mfb_dragGC,
                        curX, ytop, cursorwidth, mfb_fontHeight);
        }
    }
}
