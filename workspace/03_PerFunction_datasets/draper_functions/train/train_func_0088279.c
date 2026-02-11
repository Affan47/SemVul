write_note(object *pl, object *item, const char *msg, object *skill) {
    char buf[BOOK_BUF];
    object *newBook = NULL;


    if (!item || item->type != BOOK)
        return 0;

    if (!msg) {
        draw_ext_info_format(NDI_UNIQUE, 0, pl, MSG_TYPE_SKILL, MSG_TYPE_SKILL_ERROR,
                             "No message to write!\nUsage: use_skill %s <message>",
                             skill->skill);
        return 0;
    }
    if (strcasestr_local(msg, "endmsg")) {
        draw_ext_info(NDI_UNIQUE, 0, pl, MSG_TYPE_SKILL, MSG_TYPE_SKILL_ERROR,
                      "Trying to cheat now are we?");
        return 0;
    }


    if (execute_event(item, EVENT_TRIGGER, pl, NULL, msg, SCRIPT_FIX_ALL) != 0)
        return strlen(msg);

    buf[0] = 0;
    if (!book_overflow(item->msg, msg, BOOK_BUF)) {
        if (item->msg)
            snprintf(buf, sizeof(buf), "%s%s\n", item->msg, msg);
        else
            snprintf(buf, sizeof(buf), "%s\n", msg);

        if (item->nrof > 1) {
            newBook = object_new();
            object_copy(item, newBook);
            object_decrease_nrof_by_one(item);
            newBook->nrof = 1;
            object_set_msg(newBook, buf);
            newBook = object_insert_in_ob(newBook, pl);
        } else {
            object_set_msg(item, buf);


        }
        query_short_name(item, buf, BOOK_BUF);
        draw_ext_info_format(NDI_UNIQUE, 0, pl, MSG_TYPE_SKILL, MSG_TYPE_SKILL_SUCCESS,
                             "You write in the %s.",
                             buf);
        return strlen(msg);
    }

    query_short_name(item, buf, BOOK_BUF);
    draw_ext_info_format(NDI_UNIQUE, 0, pl, MSG_TYPE_SKILL, MSG_TYPE_SKILL_FAILURE,
                         "Your message won't fit in the %s!",
                         buf);
    return 0;
}
