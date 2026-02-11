xim_init(void)
{
    GSList *it;
    gchar *aname, *aclass;

    aname = g_strdup(g_get_prgname());
    if (!aname) aname = g_strdup("obt");

    aclass = g_strdup(aname);
    if (g_ascii_islower(aclass[0]))
        aclass[0] = g_ascii_toupper(aclass[0]);

    xim = XOpenIM(obt_display, NULL, aname, aclass);

    if (!xim)
        g_message("Failed to open an Input Method");
    else {
        XIMStyles *xim_styles = NULL;
        char *r;


        r = XGetIMValues(xim, XNQueryInputStyle, &xim_styles, NULL);
        if (r || !xim_styles)
            g_message("Input Method does not support any styles");
        if (xim_styles) {
            int i;


            for (i = 0; i < xim_styles->count_styles; ++i) {
                if (xim_styles->supported_styles[i] ==
                    (XIMPreeditNothing | XIMStatusNothing))
                {
                    xim_style = xim_styles->supported_styles[i];
                    break;
                }
            }
            XFree(xim_styles);
        }

        if (!xim_style) {
            g_message("Input Method does not support a usable style");

            XCloseIM(xim);
            xim = NULL;
        }
    }


    for (it = xic_all; it; it = g_slist_next(it))
        obt_keyboard_context_renew(it->data);

    g_free(aclass);
    g_free(aname);
}
