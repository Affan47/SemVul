build_class_list_reply(SockList *sl) {
    archetype *cl;

    SockList_Reset(sl);
    SockList_AddString(sl, "replyinfo class_list ");

    for (cl = first_archetype; cl; cl = cl->next) {
        if (cl->clone.type == CLASS) {
            SockList_AddPrintf(sl, "|%s", cl->name);
        }
    }
}
