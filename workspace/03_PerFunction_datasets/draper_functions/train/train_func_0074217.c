animate_object(object *op, int dir) {
    int max_state;
    int base_state;
    int oldface = op->face->number;

    if (!op->animation_id || !NUM_ANIMATIONS(op)) {
        StringBuffer *sb;
        char *diff;

        LOG(llevError, "Object lacks animation.\n");
        sb = stringbuffer_new();
        object_dump(op, sb);
        diff = stringbuffer_finish(sb);
        LOG(llevError, "%s", diff);
        free(diff);
        return;
    }

    if (op->head) {
        dir = op->head->direction;

        if (NUM_ANIMATIONS(op) == NUM_ANIMATIONS(op->head))
            op->state = op->head->state;
    } else if (QUERY_FLAG(op, FLAG_IS_TURNABLE)) {
        dir = op->direction;
    }


    max_state = NUM_ANIMATIONS(op)/NUM_FACINGS(op);
    base_state = 0;


    if (NUM_FACINGS(op) == 2) {
        if (dir < 5)
            base_state = 0;
        else
            base_state = NUM_ANIMATIONS(op)/2;
    } else if (NUM_FACINGS(op) == 4) {
        if (dir == 0)
            base_state = 0;
        else
            base_state = ((dir-1)/2)*(NUM_ANIMATIONS(op)/4);
    } else if (NUM_FACINGS(op) == 8) {
        if (dir == 0)
            base_state = 0;
        else
            base_state = (dir-1)*(NUM_ANIMATIONS(op)/8);
    } else if (QUERY_FLAG(op, FLAG_IS_TURNABLE)) {
        base_state = (NUM_ANIMATIONS(op) / 9) * (dir);
        max_state = NUM_ANIMATIONS(op) / 9;
    }


    if (op->state >= max_state) {
        op->state = 0;
        if (op->temp_animation_id) {
            op->temp_animation_id = 0;
            animate_object(op, dir);
            return;
        }
    }
    SET_ANIMATION(op, op->state+base_state);

    if (op->face == blank_face)
        op->invisible = 1;


    else if (op->type != PLAYER && QUERY_FLAG((&op->arch->clone), FLAG_ALIVE)) {
        if (op->face->number == 0) {
            op->invisible = 1;
            CLEAR_FLAG(op, FLAG_ALIVE);
        } else {
            op->invisible = 0;
            SET_FLAG(op, FLAG_ALIVE);
        }
    }

    if (op->more)
        animate_object(op->more, dir);


    if (!op->head && (oldface != op->face->number))
        object_update(op, UP_OBJ_FACE);
}
