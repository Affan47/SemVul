get_player_archetype(archetype *at) {
    archetype *start = at;

    for (;;) {
        if (at == NULL || at->next == NULL)
            at = first_archetype;
        else
            at = at->next;
        if (at->clone.type == PLAYER)
            return at;
        if (at == start) {
            LOG(llevError, "No Player archetypes\n");
            exit(-1);
        }
    }
}
