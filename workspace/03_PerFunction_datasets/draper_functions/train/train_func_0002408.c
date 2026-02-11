chart_add_tick(chart_priv *c, float *val)
{
    int i;

    ENTER;
    if (!c->ticks)
        RET();
    for (i = 0; i < c->rows; i++) {
        if (val[i] < 0)
            val[i] = 0;
        if (val[i] > 1)
            val[i] = 1;
        c->ticks[i][c->pos] = val[i] * c->h;
        DBG("new wval = %uld\n", c->ticks[i][c->pos]);
    }
    c->pos = (c->pos + 1) %  c->w;
    gtk_widget_queue_draw(c->da);

    RET();
}
