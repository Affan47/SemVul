gtk_polar_view_update          (GtkWidget  *widget)
{
    GtkPolarView *polv = GTK_POLAR_VIEW (widget);
    gdouble       number, now;
    gchar        *buff;
    guint         h,m,s;
    gchar        *ch,*cm,*cs;
    sat_t        *sat = NULL;
    gint         *catnr;

    if (polv->resize) {
        update_polv_size (polv);
        polv->resize = FALSE;
    }


    if (polv->counter < polv->refresh) {
        polv->counter++;
    }
    else {

        polv->counter = 1;
        polv->naos = 2458849.5;


        g_hash_table_foreach (polv->sats, update_sat, polv);


        if (polv->eventinfo) {

            if (polv->ncat > 0) {
                catnr = g_try_new0 (gint, 1);
                *catnr = polv->ncat;
                sat = SAT(g_hash_table_lookup (polv->sats, catnr));
                g_free (catnr);


                if (sat != NULL) {

                    now = polv->tstamp;
                    number = polv->naos - now;


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

                    if (h > 0)
                        buff = g_strdup_printf (_("Next: %s\nin %s%d:%s%d%s%d"),
                                                sat->nickname, ch, h, cm, m, cs, s);
                    else
                        buff = g_strdup_printf (_("Next: %s\nin %s%d%s%d"),
                                                sat->nickname, cm, m, cs, s);


                    g_object_set (polv->next,
                                  "text", buff,
                                  NULL);

                    g_free (buff);
                    g_free (ch);
                    g_free (cm);
                    g_free (cs);
                }
                else {
                    sat_log_log (SAT_LOG_LEVEL_BUG,
                                 _("%s: Can not find NEXT satellite."),
                                 __FUNCTION__);
                    g_object_set (polv->next,
                                  "text", _("Next: ERR"),
                                  NULL);
                }
            }
            else {
                g_object_set (polv->next,
                              "text", _("Next: N/A"),
                              NULL);
            }
        }
        else {
            g_object_set (polv->next,
                          "text", "",
                          NULL);
        }

    }
}
