do_item_stats(int *bytes) {
    size_t bufleft = (size_t) LARGEST_ID * 160;
    char *buffer = malloc(bufleft);
    char *bufcurr = buffer;
    rel_time_t now = current_time;
    int i;
    int linelen;

    if (buffer == NULL) {
        return NULL;
    }

    for (i = 0; i < LARGEST_ID; i++) {
        if (tails[i] != NULL) {
            linelen = snprintf(bufcurr, bufleft,
                "STAT items:%d:number %u\r\n"
                "STAT items:%d:age %u\r\n"
                "STAT items:%d:evicted %u\r\n"
                "STAT items:%d:outofmemory %u\r\n",
                    i, sizes[i], i, now - tails[i]->time, i,
                    itemstats[i].evicted, i, itemstats[i].outofmemory);
            if (linelen + sizeof("END\r\n") < bufleft) {
                bufcurr += linelen;
                bufleft -= linelen;
            }
            else {

                break;
            }
        }
    }
    memcpy(bufcurr, "END\r\n", 6);
    bufcurr += 5;

    *bytes = bufcurr - buffer;
    return buffer;
}
