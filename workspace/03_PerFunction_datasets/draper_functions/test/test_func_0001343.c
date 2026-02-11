update_selected (GtkSatMap *satmap, sat_t *sat)
{
    guint         h,m,s;
    gchar        *ch,*cm,*cs;
    gchar        *alsstr,*text;
    gdouble       number, now;
    gboolean      isgeo = FALSE;

    now = satmap->tstamp;

    if (sat->el > 0.0) {
        if (sat->los > 0.0) {
            number = sat->los - now;
            alsstr = g_strdup ("LOS");
        }
        else {
            isgeo = TRUE;
        }
    }
    else {
        if (sat->aos > 0.0) {
            number = sat->aos - now;
            alsstr = g_strdup ("AOS");
        }
        else {
            isgeo = TRUE;
        }
    }


    if (isgeo) {
        if (sat->el > 0.0) {
            text = g_strdup_printf ("<span background=\"#%s\"> %s: Always in range </span>",
                                    satmap->infobgd, sat->nickname);
        }
        else {
            text = g_strdup_printf ("<span background=\"#%s\"> %s: Always out of range </span>",
                                    satmap->infobgd, sat->nickname);
        }
    }
    else {

        s = (guint) (number * 86400);


        h = (guint) floor (s/3600);
        s -= 3600*h;


        if ((h > 0) && (h < 10))
            ch = g_strdup ("0");
        else
            ch = g_strdup ("");


        m = (guint) floor (s/60);
        s -= 60*m;


        if (m < 10)
            cm = g_strdup ("0");
        else
            cm = g_strdup ("");


        if (s < 10)
            cs = g_strdup (":0");
        else
            cs = g_strdup (":");

        if (h > 0) {
            text = g_strdup_printf ("<span background=\"#%s\"> "\
                                    "%s %s in %s%d:%s%d%s%d </span>",
                                    satmap->infobgd, sat->nickname,
                                    alsstr, ch, h, cm, m, cs, s);
        }
        else {
            text = g_strdup_printf ("<span background=\"#%s\"> "\
                                    "%s %s in %s%d%s%d </span>",
                                    satmap->infobgd, sat->nickname,
                                    alsstr, cm, m, cs, s);
        }

        g_free (ch);
        g_free (cm);
        g_free (cs);
        g_free (alsstr);
    }


    g_object_set (satmap->sel, "text", text, NULL);
    g_free (text);
}
