make_visible(object *op) {
    op->hide = 0;
    op->invisible = 0;
    if (op->type == PLAYER) {
        op->contr->tmp_invis = 0;
        if (op->contr->invis_race)
            FREE_AND_CLEAR_STR(op->contr->invis_race);
    }
    object_update(op, UP_OBJ_FACE);
}
