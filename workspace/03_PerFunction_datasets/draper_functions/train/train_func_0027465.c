obt_keyboard_keypress_to_unichar(ObtIC *ic, XEvent *ev)
{
    gunichar unikey = 0;
    KeySym sym;
    Status status;
    gchar *buf, fixbuf[4];
    gint len, bufsz;
    gboolean got_string = FALSE;

    g_return_val_if_fail(ev->type == KeyPress, 0);

    if (!ic)
        g_warning("Using obt_keyboard_keypress_to_unichar() without an "
                  "Input Context.  No i18n support!");

    if (ic && ic->xic) {
        buf = fixbuf;
        bufsz = sizeof(fixbuf);

#ifdef X_HAVE_UTF8_STRING
        len = Xutf8LookupString(ic->xic, &ev->xkey, buf, bufsz, &sym, &status);
#else
        len = XmbLookupString(ic->xic, &ev->xkey, buf, bufsz, &sym, &status);
#endif

        if (status == XBufferOverflow) {
            buf = g_new(char, len);
            bufsz = len;

#ifdef X_HAVE_UTF8_STRING
            len = Xutf8LookupString(ic->xic, &ev->xkey, buf, bufsz, &sym,
                                    &status);
#else
            len = XmbLookupString(ic->xic, &ev->xkey, buf, bufsz, &sym,
                                  &status);
#endif
        }

        if ((status == XLookupChars || status == XLookupBoth)) {
            if ((guchar)buf[0] >= 32) {
#ifndef X_HAVE_UTF8_STRING

                gchar *buf2 = buf;
                buf = g_locale_to_utf8(buf2, r, NULL, NULL, NULL);
                g_free(buf2);
#endif

                got_string = TRUE;
            }
        }
        else if (status == XLookupKeySym)

;
        else
            g_message("Bad keycode lookup. Keysym 0x%x Status: %s\n",
                      (guint) sym,
                      (status == XBufferOverflow ? "BufferOverflow" :
                       status == XLookupNone ? "XLookupNone" :
                       status == XLookupKeySym ? "XLookupKeySym" :
                       "Unknown status"));
    }
    else {
        buf = fixbuf;
        bufsz = sizeof(fixbuf);
        len = XLookupString(&ev->xkey, buf, bufsz, &sym, NULL);
        if ((guchar)buf[0] >= 32)
            got_string = TRUE;
    }

    if (got_string) {
        gunichar u = g_utf8_get_char_validated(buf, len);
        if (u && u != (gunichar)-1 && u != (gunichar)-2)
            unikey = u;
    }

    if (buf != fixbuf) g_free(buf);

    return unikey;
}
