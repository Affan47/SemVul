make_keysym(int lineno, ITEM state, ITEM q)
{


    q &= 0xffff; state &= 0xff;

    if ((q & 0xff00) == 0)
    {
        int keycode;
        int shifted=((state & KS_SHIFT) == 0) ^ ((state & KS_CAPS) == 0);
#ifndef _WIN32
        Display * display;
        display = XOpenDisplay(NULL);

        if (display)
        {
            keycode = XKeysymToKeycode (display, q & 0x7F);
            q=XKeycodeToKeysym(display, keycode, !shifted ? 0 : 1);
            XCloseDisplay(display);
        }
        else
#endif
        if (isalpha(q))
        {
            if (!shifted)
            {
                q += 0x20;
            }
        }
        else if (((state & KS_SHIFT) == 0) || ((state & KS_CAPS) == 0))
        {
            kmflcomp_warn(lineno, "Non-alphabetic virtual key sequence used with K_SHIFT or K_CAPS outside of the X environment.\n"
            "   KMFLCOMP cannot determined correct shifted keysym");
        }
        state &= ~KS_CAPS;
    }
    return q | (state<<16) | (ITEM_KEYSYM<<24);
}
