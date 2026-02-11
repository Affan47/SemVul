apply_can_apply_object(const object *who, const object *op) {
    int i, retval = 0;
    object *tmp = NULL, *ws = NULL;


    if (op->type == WEAPON || op->type == SHIELD) {
        tmp = object_find_by_type_applied(who, op->type);
        if (tmp != NULL) {
            retval = CAN_APPLY_UNAPPLY;
            ws = tmp;
        }
    }

    for (i = 0; i < NUM_BODY_LOCATIONS; i++) {
        if (op->body_info[i]) {

            if (FABS(op->body_info[i]) > who->body_info[i]) {


                retval |= CAN_APPLY_NEVER;
            } else if (who->body_used[i]+op->body_info[i] < 0) {


                object *tmp1;


                if (ws) {
                    if (who->body_used[i]-ws->body_info[i]+op->body_info[i] >= 0) {
                        retval |= CAN_APPLY_UNAPPLY;
                        continue;
                    }
                }

                tmp1 = get_item_from_body_location(who->inv, i);
                if (!tmp1)
                    retval |= CAN_APPLY_NEVER;
                else {


                    retval |= CAN_APPLY_UNAPPLY;
                    if (!tmp)
                        tmp = tmp1;
                    else if (tmp != tmp1)
                        retval |= CAN_APPLY_UNAPPLY_MULT;


                    if (who->body_used[i]-tmp1->body_info[i] != who->body_info[i]
                    && FABS(op->body_info[i]) < who->body_info[i])
                        retval |= CAN_APPLY_UNAPPLY_CHOICE;


                    if (who->body_used[i]+op->body_info[i]-tmp1->body_info[i] < 0)
                        retval |= CAN_APPLY_UNAPPLY_MULT;
                }
            }
        }
    }


    if (IS_WEAPON(op) && !QUERY_FLAG(who, FLAG_USE_WEAPON))
        retval |= CAN_APPLY_RESTRICTION;
    if (IS_SHIELD(op) && !QUERY_FLAG(who, FLAG_USE_SHIELD))
        retval |= CAN_APPLY_RESTRICTION;
    if (IS_ARMOR(op) && !QUERY_FLAG(who, FLAG_USE_ARMOUR))
        retval |= CAN_APPLY_RESTRICTION;

    if (who->type != PLAYER) {
        if ((op->type == WAND || op->type == ROD)
        && !QUERY_FLAG(who, FLAG_USE_RANGE))
            retval |= CAN_APPLY_RESTRICTION;
        if (op->type == BOW && !QUERY_FLAG(who, FLAG_USE_BOW))
            retval |= CAN_APPLY_RESTRICTION;
        if (op->type == RING && !QUERY_FLAG(who, FLAG_USE_RING))
            retval |= CAN_APPLY_RESTRICTION;
    }
    return retval;
}
