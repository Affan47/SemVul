get_archetype_by_type_subtype(int type, int subtype) {
    archetype *at;

    for (at = first_archetype; at != NULL; at = at->next) {
        if (((type == -1) || (type == at->clone.type))
        && (subtype == -1 || subtype == at->clone.subtype))
            return at;
    }
    return NULL;
}
