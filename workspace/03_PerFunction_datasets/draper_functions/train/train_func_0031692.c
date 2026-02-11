command_unarmed_skill(object *op, const char *params) {
    object *skill;
    size_t i;

    if (*params == '\0') {
        draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_CONFIG,
                             "unarmed skill is set to %s",
                             op->contr->unarmed_skill ? op->contr->unarmed_skill: "nothing");
        return;
    }


    skill = find_skill_by_name(op, params);

    if (!skill) {
        draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                             "You do not know any such skill called %s",
                             params);
        return;
    }
    for (i = 0; i < sizeof(unarmed_skills); i++)
        if (skill->subtype == unarmed_skills[i])
            break;
    if (i == sizeof(unarmed_skills)) {
        draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                             "%s is not an unarmed skill!",
                             skill->name);
        return;

    }

    if (op->contr->unarmed_skill)
        free_string(op->contr->unarmed_skill);


    op->contr->unarmed_skill = add_string(skill->name);

    draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_CONFIG,
                         "unarmed skill is now set to %s",
                         op->contr->unarmed_skill);
}
