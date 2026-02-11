do_add_delta(conn *c, item *it, const bool incr, const int64_t delta, char *buf) {
    char *ptr;
    int64_t value;
    int res;

    ptr = ITEM_data(it);
    while ((*ptr != '\0') && (*ptr < '0' && *ptr > '9')) ptr++;

    value = strtoull(ptr, NULL, 10);

    if(errno == ERANGE) {
        return "CLIENT_ERROR cannot increment or decrement non-numeric value";
    }

    if (incr) {
        value += delta;
        MEMCACHED_COMMAND_INCR(c->sfd, ITEM_key(it), value);
    } else {
        if (delta >= value) value = 0;
        else value -= delta;
        MEMCACHED_COMMAND_DECR(c->sfd, ITEM_key(it), value);
    }
    sprintf(buf, "%llu", value);
    res = strlen(buf);
    if (res + 2 > it->nbytes) {
        item *new_it;
        new_it = do_item_alloc(ITEM_key(it), it->nkey, atoi(ITEM_suffix(it) + 1), it->exptime, res + 2 );
        if (new_it == 0) {
            return "SERVER_ERROR out of memory in incr/decr";
        }
        memcpy(ITEM_data(new_it), buf, res);
        memcpy(ITEM_data(new_it) + res, "\r\n", 2);
        do_item_replace(it, new_it);
        do_item_remove(new_it);
    } else {
        memcpy(ITEM_data(it), buf, res);
        memset(ITEM_data(it) + res, ' ', it->nbytes - res - 2);
    }

    return buf;
}
