use_skill(object *op, const char *string) {
    object *skop;
    size_t len;

    if (!string)
        return 0;

    skop = NULL;
    FOR_INV_PREPARE(op, tmp) {
        if (tmp->type == SKILL
        && QUERY_FLAG(tmp, FLAG_CAN_USE_SKILL)
        && !strncasecmp(string, tmp->skill, MIN(strlen(string), strlen(tmp->skill)))) {
            skop = tmp;
            break;
        } else if (tmp->type == SKILL_TOOL
        && !strncasecmp(string, tmp->skill, MIN(strlen(string), strlen(tmp->skill)))) {
            skop = tmp;
            break;
        }
    } FOR_INV_FINISH();
    if (!skop) {
        draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_SKILL, MSG_TYPE_SKILL_MISSING,
                             "Unable to find skill %s",
                             string);
        return 0;
    }

    len = strlen(skop->skill);


    if (len >= strlen(string)) {
        string = NULL;
    } else {
        string += len;
        while (*string == 0x20)
            string++;
        if (strlen(string) == 0)
            string = NULL;
    }

#ifdef SKILL_UTIL_DEBUG
    LOG(llevDebug, "use_skill() got skill: %s\n", sknum > -1 ? skills[sknum].name : "none");
#endif


    if (do_skill(op, op, skop, op->facing, string))
        return 1;

    return 0;
}
