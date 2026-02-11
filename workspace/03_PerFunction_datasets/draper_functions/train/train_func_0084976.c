cast_invisible(object *op, object *caster, object *spell_ob) {
    object *tmp;

    if (op->invisible > 1000) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SPELL, MSG_TYPE_SPELL_FAILURE,
                      "You can not extend the duration of your invisibility any further");
        return 0;
    }


    op->invisible += spell_ob->duration+SP_level_duration_adjust(caster, spell_ob);

    if (op->invisible > 1000)
        op->invisible = 1000;

    if (op->type == PLAYER) {
        if (op->contr->invis_race)
            FREE_AND_CLEAR_STR(op->contr->invis_race);
        if (spell_ob->race)
            op->contr->invis_race = add_refcount(spell_ob->race);
        if (QUERY_FLAG(spell_ob, FLAG_MAKE_INVIS))
            op->contr->tmp_invis = 0;
        else
            op->contr->tmp_invis = 1;

        op->contr->hidden = 0;
    }
    if (makes_invisible_to(op, op))
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SPELL, MSG_TYPE_SPELL_SUCCESS,
                      "You can't see your hands!");
    else
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SPELL, MSG_TYPE_SPELL_SUCCESS,
                      "You feel more transparent!");

    object_update(op, UP_OBJ_FACE);


    for (tmp = active_objects; tmp != NULL; tmp = tmp->active_next)
        if (tmp->enemy == op)
            object_set_enemy(tmp, NULL);
    return 1;
}
