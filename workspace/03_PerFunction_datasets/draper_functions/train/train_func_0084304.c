grab_keyboard_full(gboolean grab)
{
    gboolean ret = FALSE;

    if (grab) {
        if (kgrabs++ == 0) {
            ret = XGrabKeyboard(obt_display, grab_window(),
                                False, GrabModeAsync, GrabModeAsync,
                                event_time()) == Success;
            if (!ret)
                --kgrabs;
            else {
                passive_count = 0;
                grab_time = event_time();
            }
        } else
            ret = TRUE;
    } else if (kgrabs > 0) {
        if (--kgrabs == 0) {
            XUngrabKeyboard(obt_display, ungrab_time());
        }
        ret = TRUE;
    }

    return ret;
}
