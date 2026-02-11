driver_name (guint maj,
             guint min)
{
        struct stat   sbuf;
        tty_map_node *tmn;
        char         *tty;

        if (! tty_map) {
                load_drivers ();
        }
        if (tty_map == (tty_map_node *) - 1) {
                return 0;
        }

        tmn = tty_map;
        for (;;) {
                if (! tmn) {
                        return 0;
                }
                if (tmn->major_number == maj && tmn->minor_first <= min && tmn->minor_last >= min) {
                        break;
                }
                tmn = tmn->next;
        }

        tty = g_strdup_printf (_PATH_DEV "%s%d", tmn->name, min);
        if (stat (tty, &sbuf) < 0){
                g_free (tty);

                if (tmn->devfs_type) {
                        return NULL;
                }

                tty = g_strdup_printf (_PATH_DEV "%s", tmn->name);

                if (stat (tty, &sbuf) < 0) {
                        g_free (tty);
                        return NULL;
                }
        }

        if (min != MINOR_OF (sbuf.st_rdev)) {
                g_free (tty);
                return NULL;
        }

        if (maj != MAJOR_OF (sbuf.st_rdev)) {
                g_free (tty);
                return NULL;
        }

        return tty;
}
