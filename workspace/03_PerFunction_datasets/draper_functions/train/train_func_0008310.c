parse_attributes(MatchEquityParser * parser, const gchar ** attr_names, const gchar ** attr_values)
{
    gint i = 0;
    while (attr_names[i]) {
        if (strcmp(attr_names[i], "type") == 0) {
            if (strcmp(attr_values[i], "explicit") == 0)
                parser->type = TYPE_EXPLICIT;
            else if (strcmp(attr_values[i], "mec") == 0)
                parser->type = TYPE_MEC;
            else if (strcmp(attr_values[i], "zadeh") == 0)
                parser->type = TYPE_ZADEH;
        } else if (strcmp(attr_names[i], "player") == 0) {
            if (strcmp(attr_values[i], "both") == 0)
                parser->player = MP_PLAYER_BOTH;
            if (strcmp(attr_values[i], "0") == 0)
                parser->player = MP_PLAYER_0;
            if (strcmp(attr_values[i], "1") == 0)
                parser->player = MP_PLAYER_1;
        }
        i++;
    }
}
