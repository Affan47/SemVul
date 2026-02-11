add_arch(archetype *at) {
    unsigned long index = hasharch(at->name, ARCHTABLE), org_index = index;

    for (;;) {
        if (arch_table[index] == NULL) {
            arch_table[index] = at;
            return;
        }
        if (++index == ARCHTABLE)
            index = 0;
        if (index == org_index)
            fatal(ARCHTABLE_TOO_SMALL);
    }
}
