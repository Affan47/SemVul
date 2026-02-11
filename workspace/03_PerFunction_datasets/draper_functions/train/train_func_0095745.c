quest_get_player_state(player *pl, sstring quest_code) {
    quest_player *q = get_or_create_quest(pl);
    quest_state *s = get_state(q, quest_code);
    quest_definition *quest = quest_get(quest_code);

    if (!s)
        return 0;

    if (s->state == QC_CAN_RESTART && quest && quest->quest_restart)
        return 0;

    return s->state;
}
