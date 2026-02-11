apply_check_apply_restrictions(object *who, object *op, int aflags) {
    int i;

    i = apply_can_apply_object(who, op);
    if (i == 0)
        return 1;


    if (i&CAN_APPLY_NEVER) {
        if (!(aflags&AP_NOPRINT)) {
            char name_op[MAX_BUF];

            query_name(op, name_op, MAX_BUF);
            draw_ext_info_format(NDI_UNIQUE, 0, who, MSG_TYPE_APPLY, MSG_TYPE_APPLY_BADBODY,
                "You don't have the body to use a %s",
                name_op);
        }
        return 0;
    }

    if (i&CAN_APPLY_RESTRICTION) {
        if (!(aflags&AP_NOPRINT)) {
            char name_op[MAX_BUF];

            query_name(op, name_op, MAX_BUF);
            draw_ext_info_format(NDI_UNIQUE, 0, who, MSG_TYPE_APPLY, MSG_TYPE_APPLY_PROHIBITION,
                "You have a prohibition against using a %s",
                name_op);
        }
        return 0;
    }

    if (who->type != PLAYER) {

        return !unapply_for_ob(who, op, aflags);
    }

    if (who->contr->unapply == unapply_never
    || (i&CAN_APPLY_UNAPPLY_CHOICE && who->contr->unapply == unapply_nochoice)) {
        if (!(aflags&AP_NOPRINT))
            draw_ext_info(NDI_UNIQUE, 0, who, MSG_TYPE_APPLY, MSG_TYPE_APPLY_UNAPPLY,
                "You need to unapply some item(s):");
        unapply_for_ob(who, op, AP_PRINT);
        return 0;
    }

    if (who->contr->unapply == unapply_always
    || !(i&CAN_APPLY_UNAPPLY_CHOICE)) {
        return !unapply_for_ob(who, op, aflags);
    }

    return 1;
}
