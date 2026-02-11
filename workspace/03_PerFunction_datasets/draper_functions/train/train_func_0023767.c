command_throw(object *op, const char *params) {
    object *skop;

    skop = find_skill_by_name(op, skill_names[SK_THROWING]);
    if (skop) {
        do_skill(op, op, skop, op->facing, *params == '\0' ? NULL : params);
        return;
    }

    draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_SKILL, MSG_TYPE_SKILL_MISSING,
                  "You have no knowledge of the skill throwing.");
}
