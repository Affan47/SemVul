record_set_line (UTMP       *u,
                 const char *display_device,
                 const char *x11_display_name)
{


        if (display_device != NULL
            && g_str_has_prefix (display_device, "/dev/")) {
                strncpy (u->ut_line,
                         display_device + strlen ("/dev/"),
                         sizeof (u->ut_line));
        } else if (x11_display_name != NULL
                   && g_str_has_prefix (x11_display_name, ":")) {
                strncpy (u->ut_line,
                         x11_display_name,
                         sizeof (u->ut_line));
        }

        g_debug ("using ut_line %.*s", (int) sizeof (u->ut_line), u->ut_line);
}
