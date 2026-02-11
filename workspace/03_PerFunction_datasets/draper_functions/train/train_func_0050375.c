resist_size_windows(ObClient *c, gint resist, gint *w, gint *h,
                         ObDirection dir)
{
    GList *it;
    ObClient *target;
    Rect dock_area;

    if (!resist) return;

    for (it = stacking_list; it; it = g_list_next(it)) {
        if (!WINDOW_IS_CLIENT(it->data))
            continue;
        target = it->data;


        if (!target->frame->visible || target == c)
            continue;

        if (target->below && !c->below && target->skip_taskbar)
            continue;

        if (resist_size_window(c->frame->area, target->frame->area,
                               resist, w, h, dir))
            break;
    }
    dock_get_area(&dock_area);
    resist_size_window(c->frame->area, dock_area,
                       resist, w, h, dir);
}
