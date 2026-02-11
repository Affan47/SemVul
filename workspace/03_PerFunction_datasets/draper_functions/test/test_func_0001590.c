spellpath_msg(int level, size_t booksize, StringBuffer *buf) {
    int path = RANDOM()%NRSPELLPATHS, prayers = RANDOM()%2;
    int did_first_sp = 0;
    uint32 pnum = spellpathdef[path];
    archetype *at;

    if (buf == NULL) {
        buf = stringbuffer_new();

        stringbuffer_append_printf(buf, "Herein are detailed the names of %s", prayers ? "prayers" : "incantations");
        stringbuffer_append_printf(buf, " belonging to the path of %s:\n ", spellpathnames[path]);
    }

    for (at = first_archetype; at != NULL; at = at->next) {


        if (at->clone.type == SPELL
        && at->clone.path_attuned&pnum
        && ((at->clone.stats.grace && prayers) || (at->clone.stats.sp && !prayers))
        && at->clone.level < level*8) {
            if (strlen(at->clone.name) + stringbuffer_length(buf) >= booksize)
                break;

            if (did_first_sp)
                stringbuffer_append_string(buf, ",\n ");
            did_first_sp = 1;
            stringbuffer_append_string(buf,at->clone.name);
        }
    }


    if (!did_first_sp) {
        if (RANDOM()%4) {
            return spellpath_msg(level, booksize, buf);
        }

        stringbuffer_append_string(buf, "- no known spells exist -\n");
    }
    return buf;
}
