profile_find_node(struct profile_node *section, const char *name,
                            const char *value, int section_flag, void **state,
                            struct profile_node **node)
{
    struct profile_node *p;

    CHECK_MAGIC(section);
    p = *state;
    if (p) {
        CHECK_MAGIC(p);
    } else
        p = section->first_child;

    for (; p; p = p->next) {
        if (name && (strcmp(p->name, name)))
            continue;
        if (section_flag) {
            if (p->value)
                continue;
        } else {
            if (!p->value)
                continue;
            if (value && (strcmp(p->value, value)))
                continue;
        }
        if (p->deleted)
            continue;

        if (node)
            *node = p;
        break;
    }
    if (p == 0) {
        *state = 0;
        return section_flag ? PROF_NO_SECTION : PROF_NO_RELATION;
    }


    for (p = p->next; p; p = p->next) {
        if (name && (strcmp(p->name, name)))
            continue;
        if (section_flag) {
            if (p->value)
                continue;
        } else {
            if (!p->value)
                continue;
            if (value && (strcmp(p->value, value)))
                continue;
        }

        break;
    }
    *state = p;
    return 0;
}
