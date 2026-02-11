game_type_name(GameType type)
{
    gint ii = 0;
    for (ii = 0; ii < GAME_TYPE_TABLE_SIZE; ii++) {
        if (type == game_type_table[ii].type)
            return game_type_table[ii].name;
    }

    return NULL;
}
