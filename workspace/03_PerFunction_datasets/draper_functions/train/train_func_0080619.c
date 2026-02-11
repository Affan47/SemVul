command_getm(char * token, Channel * c) {
    GetmArgs args;

    args.locs = read_location_list(&c->inp, &args.locs_cnt);
    if (read_stream(&c->inp) != 0) exception(ERR_JSON_SYNTAX);
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);

    strlcpy(args.token, token, sizeof(args.token));
    cache_enter(command_getm_cache_client, c, &args, sizeof(args));
}
