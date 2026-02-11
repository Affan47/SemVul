trapdoor_type_move_on(ob_methods *context, object *trap, object *victim, object *originator) {
    int max, sound_was_played;
    object *ab, *ab_next;
    if (common_pre_ob_move_on(trap, victim, originator) == METHOD_ERROR)
        return METHOD_OK;
    if (!trap->value) {
        int tot;

        for (ab = trap->above, tot = 0; ab != NULL; ab = ab->above)
            if ((ab->move_type && trap->move_on) || ab->move_type == 0)
                tot += (ab->nrof ? ab->nrof : 1)*ab->weight+ab->carrying;

        if (!(trap->value = (tot > trap->weight) ? 1 : 0)) {
            common_post_ob_move_on(trap, victim, originator);
            return METHOD_OK;
        }
        SET_ANIMATION(trap, trap->value);
        object_update(trap, UP_OBJ_FACE);
    }

    for (ab = trap->above, max = 100, sound_was_played = 0; --max && ab; ab = ab_next) {


        ab_next = ab->above;

        if ((ab->move_type && trap->move_on) || ab->move_type == 0) {
            if (!sound_was_played) {
                play_sound_map(SOUND_TYPE_GROUND, trap, 0, "fall hole");
                sound_was_played = 1;
            }
            draw_ext_info(NDI_UNIQUE, 0, ab, MSG_TYPE_APPLY, MSG_TYPE_APPLY_TRAP,
                  "You fall into a trapdoor!");
            transfer_ob(ab, (int)EXIT_X(trap), (int)EXIT_Y(trap), 0, ab);
        }
    }
    common_post_ob_move_on(trap, victim, originator);
    return METHOD_OK;
}
