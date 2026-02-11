cast_word_of_recall(object *op, object *caster, object *spell_ob) {
    object *dummy;
    int time;

    if (op->type != PLAYER)
        return 0;

    if (object_find_by_type_subtype(op, SPELL_EFFECT, SP_WORD_OF_RECALL)) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SPELL, MSG_TYPE_SPELL_SUCCESS,
                      "You feel a force starting to build up inside you.");
        return 1;
    }

    dummy = create_archetype(FORCE_NAME);
    if (dummy == NULL) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SPELL, MSG_TYPE_SPELL_ERROR,
                      "Oops, program error!");
        LOG(llevError, "cast_word_of_recall: create_archetype(force) failed!\n");
        return 0;
    }
    time = spell_ob->duration-SP_level_duration_adjust(caster, spell_ob);
    if (time < 1)
        time = 1;


    dummy->speed = 0.002;
    object_update_speed(dummy);
    dummy->speed_left = -dummy->speed*time;
    dummy->type = SPELL_EFFECT;
    dummy->subtype = SP_WORD_OF_RECALL;


    EXIT_PATH(dummy) = add_string(op->contr->savebed_map);
    EXIT_X(dummy) = op->contr->bed_x;
    EXIT_Y(dummy) = op->contr->bed_y;

    (void)object_insert_in_ob(dummy, op);
    draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SPELL, MSG_TYPE_SPELL_SUCCESS,
                  "You feel a force starting to build up inside you.");
    return 1;
}
