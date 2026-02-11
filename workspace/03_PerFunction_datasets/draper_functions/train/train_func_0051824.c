print_inventory(item *op) {
    char buf[MAX_BUF];
    char buf2[MAX_BUF];
    item *tmp;
    static int l = 0;
#if 0
    int info_width = get_info_width();
#else


    int info_width = 40;
#endif

    if (l == 0) {
        snprintf(buf, sizeof(buf), "%s's inventory (%d):", op->d_name, op->tag);
        snprintf(buf2, sizeof(buf2), "%-*s%6.1f kg", info_width-10, buf, op->weight);
        draw_ext_info(NDI_BLACK, MSG_TYPE_CLIENT, MSG_TYPE_CLIENT_DEBUG, buf2);
    }

    l += 2;
    for (tmp = op->inv; tmp; tmp = tmp->next) {
        snprintf(buf, sizeof(buf), "%*s- %d %s%s (%d)", l-2, "", tmp->nrof, tmp->d_name, tmp->flags, tmp->tag);
        snprintf(buf2, sizeof(buf2), "%-*s%6.1f kg", info_width-8-l, buf, tmp->nrof*tmp->weight);
        draw_ext_info(NDI_BLACK, MSG_TYPE_CLIENT, MSG_TYPE_CLIENT_DEBUG, buf2);
        if (tmp->inv) {
            print_inventory(tmp);
        }
    }
    l -= 2;
}
