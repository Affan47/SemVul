hide(object *op, object *skill) {


    if (QUERY_FLAG(op, FLAG_MAKE_INVIS)) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SKILL, MSG_TYPE_SKILL_ERROR,
                      "You don't need to hide while invisible!");
        return 0;
    }

    if (!op->hide && op->invisible > 0 && op->type == PLAYER) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_ATTRIBUTE, MSG_TYPE_ATTRIBUTE_GOOD_EFFECT_END,
                      "Your attempt to hide breaks the invisibility spell!");
        make_visible(op);
    }

    if (op->invisible > 50*skill->level) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SKILL, MSG_TYPE_SKILL_ERROR,
                      "You are as hidden as you can get.");
        return 0;
    }

    if (attempt_hide(op, skill)) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SKILL, MSG_TYPE_SKILL_SUCCESS,
                      "You hide in the shadows.");
        object_update(op, UP_OBJ_FACE);
        return calc_skill_exp(op, NULL, skill);
    }
    draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SKILL, MSG_TYPE_SKILL_FAILURE,
                  "You fail to conceal yourself.");
    return 0;
}
