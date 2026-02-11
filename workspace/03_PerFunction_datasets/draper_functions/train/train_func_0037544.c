monster_apply_below(object *monster) {
    FOR_BELOW_PREPARE(monster, tmp) {
        switch (tmp->type) {
        case CF_HANDLE:
        case TRIGGER:
            if (monster->will_apply&WILL_APPLY_HANDLE)
                apply_manual(monster, tmp, 0);
            break;

        case TREASURE:
            if (monster->will_apply&WILL_APPLY_TREASURE)
                apply_manual(monster, tmp, 0);
            break;
        }
        if (QUERY_FLAG(tmp, FLAG_IS_FLOOR))
            break;
    } FOR_BELOW_FINISH();
}
