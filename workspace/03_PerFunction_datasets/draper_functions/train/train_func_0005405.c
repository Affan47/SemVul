meter_set_icons(meter_priv *m, gchar **icons)
{
    gchar **s;

    ENTER;
    if (m->icons == icons)
        RET();
    for (s = icons; *s; s++)
        DBG("icon %s\n", *s);
    m->num = (s - icons);
    DBG("total %d icons\n", m->num);
    m->icons = icons;
    m->cur_icon = -1;
    m->level = -1;
    RET();
}
