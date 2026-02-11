caster_level(const object *caster, const object *spell) {
    int level = caster->level;


    if (caster->type == PLAYER && spell->skill) {
        int i;

        for (i = 0; i < NUM_SKILLS; i++)
            if (caster->contr->last_skill_ob[i]
            && caster->contr->last_skill_ob[i]->skill == spell->skill) {
                level = caster->contr->last_skill_ob[i]->level;
                break;
            }
    }

    level += ((caster->path_repelled&spell->path_attuned) ? -2 : 0)
            +((caster->path_attuned&spell->path_attuned) ? 2 : 0);


    if (level < 1)
        level = 1;
    return level;
}
