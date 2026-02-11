request_info_cmd(char *buf, int len, socket_struct *ns) {
    char *params = NULL, *cp;

    SockList sl;


    SockList_Init(&sl);
    SockList_AddString(&sl, "replyinfo ");
    SockList_AddString(&sl, buf);


    for (cp = buf; *cp != '\0'; cp++)
        if (*cp == ' ') {
            *cp = '\0';
            params = cp+1;
            break;
        }
    if (!strcmp(buf, "image_info"))
        send_image_info(ns, params);
    else if (!strcmp(buf, "image_sums"))
        send_image_sums(ns, params);
    else if (!strcmp(buf, "skill_info"))
        send_skill_info(ns, params);
    else if (!strcmp(buf, "spell_paths"))
        send_spell_paths(ns, params);
    else if (!strcmp(buf, "exp_table"))
        send_exp_table(ns, params);
    else if (!strcmp(buf, "race_list"))
        send_race_list(ns, params);
    else if (!strcmp(buf, "race_info"))
        send_race_info(ns, params);
    else if (!strcmp(buf, "class_list"))
        send_class_list(ns, params);
    else if (!strcmp(buf, "class_info"))
        send_class_info(ns, params);
    else if (!strcmp(buf, "rules"))
        send_file(ns, "rules");
    else if (!strcmp(buf, "motd"))
        send_file(ns, "motd");
    else if (!strcmp(buf, "news"))
        send_file(ns, "news");
    else if (!strcmp(buf,"newcharinfo"))
        send_new_char_info(ns);
    else if (!strcmp(buf,"startingmap"))
        send_map_info(ns);
    else if (!strcmp(buf, "knowledge_info"))
        knowledge_send_info(ns);
    else
        Send_With_Handling(ns, &sl);
    SockList_Term(&sl);
}
