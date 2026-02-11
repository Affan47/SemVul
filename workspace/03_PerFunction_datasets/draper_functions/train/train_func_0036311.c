effect (const Event& e, Tool31& tool) {
    boolean flag = true;
    Window* w = e.window();
    if (w != nil) {
        w->cursor(window_cursor);
        Canvas* c = w->canvas();
        long count = _gr_list->count();
        Coord l, b, r, t;
        for (long i = 0; i < count && flag; i++) {
            Graphic31* target = _gr_list->item(i);
            target->getbounds(l, b, r, t);
            c->damage(l, b, r, t);
            flag = target->effect(e, tool);
            if (flag) {
                target->getbounds(l, b, r, t);
                c->damage(l, b, r, t);
            }
            target->flush();
            CanvasRep& rep = *c->rep();
            CanvasDamage& cd = rep.damage_;
            rep.start_repair();
            drawclipped(c, cd.left, cd.bottom, cd.right, cd.top);
            rep.finish_repair();
        }
        _gr_list->remove_all();
    }
    return flag;
}
