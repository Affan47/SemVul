gs_op_language_level(void)
{
    const op_def *const *tptr;
    int level = 1;

    for (tptr = op_defs_all; *tptr != 0; ++tptr) {
        const op_def *def;

        for (def = *tptr; def->oname != 0; ++def)
            if (op_def_is_begin_dict(def)) {
                if (!strcmp(def->oname, "level2dict"))
                    level = max(level, 2);
                else if (!strcmp(def->oname, "ll3dict"))
                    level = max(level, 3);
            }
    }
    return level;
}
