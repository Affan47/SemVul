find_treasure_by_name(const treasure *t, const char *name, int depth) {
    treasurelist *tl;
    archetype *at;

    if (depth > 10)
        return NULL;

    while (t != NULL) {
        if (t->name != NULL) {
            tl = find_treasurelist(t->name);
            at = find_treasure_by_name(tl->items, name, depth+1);
            if (at != NULL)
                return at;
        } else {
            if (!strcasecmp(t->item->clone.name, name))
                return t->item;
        }
        if (t->next_yes != NULL) {
            at = find_treasure_by_name(t->next_yes, name, depth);
            if (at != NULL)
                return at;
        }
        if (t->next_no != NULL) {
            at = find_treasure_by_name(t->next_no, name, depth);
            if (at != NULL)
                return at;
        }
        t = t->next;
    }
    return NULL;
}
