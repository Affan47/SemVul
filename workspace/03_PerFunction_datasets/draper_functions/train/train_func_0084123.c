device_set_property (XDevice        *xdevice,
                     const char     *device_name,
                     PropertyHelper *property)
{
        int rc, i;
        Atom prop;
        Atom realtype;
        int realformat;
        unsigned long nitems, bytes_after;
        unsigned char *data;

        prop = XInternAtom (GDK_DISPLAY_XDISPLAY (gdk_display_get_default ()),
                            property->name, False);
        if (!prop)
                return FALSE;

        gdk_error_trap_push ();

        rc = XGetDeviceProperty (GDK_DISPLAY_XDISPLAY (gdk_display_get_default ()),
                                 xdevice, prop, 0, property->nitems, False,
                                 AnyPropertyType, &realtype, &realformat, &nitems,
                                 &bytes_after, &data);

        if (rc != Success ||
            realtype != property->type ||
            realformat != property->format ||
            nitems < property->nitems) {
                gdk_error_trap_pop_ignored ();
                g_warning ("Error reading property \"%s\" for \"%s\"", property->name, device_name);
                return FALSE;
        }

        for (i = 0; i < nitems; i++) {
                switch (property->format) {
                        case 8:
                                data[i] = property->data.c[i];
                                break;
                        case 32:
                                ((long*)data)[i] = property->data.i[i];
                                break;
                }
        }

        XChangeDeviceProperty (GDK_DISPLAY_XDISPLAY (gdk_display_get_default ()),
                               xdevice, prop, realtype, realformat,
                               PropModeReplace, data, nitems);

        XFree (data);

        if (gdk_error_trap_pop ()) {
                g_warning ("Error in setting \"%s\" for \"%s\"", property->name, device_name);
                return FALSE;
        }

        return TRUE;
}
