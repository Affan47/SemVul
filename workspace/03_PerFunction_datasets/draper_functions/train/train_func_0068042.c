knowledge_get_or_create(const player *pl) {
    knowledge_player *cur = knowledge_global;

    while (cur) {
        if (cur->player_name == pl->ob->name)
            return cur;
        cur = cur->next;
    }

    cur = calloc(1, sizeof(knowledge_player));
    if (!cur)
        fatal(OUT_OF_MEMORY);
    cur->player_name = add_refcount(pl->ob->name);
    cur->next = knowledge_global;
    knowledge_global = cur;

    knowledge_read_player_data(cur);
    if (pl->socket.notifications < 2)
        cur->sent_up_to = -1;
    return cur;
}
