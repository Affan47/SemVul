knowledge_first_player_save(player *pl) {
    knowledge_player *cur = knowledge_global;

    while (cur) {
        if (cur->player_name == pl->ob->name) {
            knowledge_write_player_data(cur);
        }
        cur = cur->next;
    }

}
