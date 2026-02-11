action_makes_visible(object *op) {
    if (op->invisible && QUERY_FLAG(op, FLAG_ALIVE)) {
        if (QUERY_FLAG(op, FLAG_MAKE_INVIS))
            return 0;

        if (op->contr && op->contr->tmp_invis == 0)
            return 0;


        if (op->hide || !op->contr || (op->contr && op->contr->tmp_invis)) {
            draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_MISC, MSG_SUBTYPE_NONE,
                                 "You become %s!",
                                 op->hide ? "unhidden" : "visible");
            return 1;
        }
    }
    return 0;
}
