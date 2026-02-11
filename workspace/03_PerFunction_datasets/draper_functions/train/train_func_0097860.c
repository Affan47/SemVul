mark_live(struct fa *fa) {
    int changed;

    F(mark_reachable(fa));

    list_for_each(s, fa->initial) {
        s->live = s->reachable && s->accept;
    }

    do {
        changed = 0;
        list_for_each(s, fa->initial) {
            if (! s->live && s->reachable) {
                for_each_trans(t, s) {
                    if (t->to->live) {
                        s->live = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    } while (changed);
    return 0;
 error:
    return -1;
}
