query_short_name(const object *op, char *buf, size_t size) {
    size_t len = 0;

    if (op->name == NULL) {
        snprintf(buf, size, "(null)");
        return;
    }
    if (!op->nrof && !op->weight && !op->title && !is_magical(op)) {
        snprintf(buf, size, "%s", op->name);
        return;
    }
    buf[0] = '\0';

    if (op->nrof <= 1)
        safe_strcat(buf, op->name, &len, size);
    else
        safe_strcat(buf, op->name_pl, &len, size);

    if (op->title && QUERY_FLAG(op, FLAG_IDENTIFIED)) {
        safe_strcat(buf, " ", &len, size);
        safe_strcat(buf, op->title, &len, size);
    }

    switch (op->type) {
    case SPELLBOOK:
    case SCROLL:
    case WAND:
    case ROD:
        if (QUERY_FLAG(op, FLAG_IDENTIFIED) || QUERY_FLAG(op, FLAG_BEEN_APPLIED)) {
            if (!op->title) {
                safe_strcat(buf, " of ", &len, size);
                if (op->inv)
                    safe_strcat(buf, op->inv->name, &len, size);
                else
                    LOG(llevError, "Spellbook %s lacks inventory\n", op->name);
            }
            if (op->type != SPELLBOOK) {
                snprintf(buf+len, size-len, " (lvl %d)", op->level);
                len += strlen(buf+len);
            }
        }
        break;

    case SKILL:
    case AMULET:
    case RING:
        if (!op->title) {

            char* desc;

            desc = stringbuffer_finish(ring_desc(op, NULL));
            if (desc[0]) {
                safe_strcat(buf, " ", &len, size);
                safe_strcat(buf, desc, &len, size);
            }
            free(desc);
        }
        break;

    default:
        if (op->magic
        && ((QUERY_FLAG(op, FLAG_BEEN_APPLIED) && need_identify(op)) || QUERY_FLAG(op, FLAG_IDENTIFIED))) {
            snprintf(buf+len, size-len, " %+d", op->magic);
            len += strlen(buf+len);
        }
    }
}
