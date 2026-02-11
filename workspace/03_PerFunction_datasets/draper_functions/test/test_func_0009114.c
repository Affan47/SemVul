change_object(object *op) {
    object *env;
    int i;
    int friendly;
    int unaggressive;
    object *owner;

    if (op->other_arch == NULL) {
        LOG(llevError, "Change object (%s) without other_arch error.\n", op->name);
        return;
    }


    if (!QUERY_FLAG(op, FLAG_ALIVE)) {
        if (op->stats.food-- > 0)
            return;
        else
            op->stats.food = 1;
    }

    env = op->env;
    object_remove(op);
    friendly = QUERY_FLAG(op, FLAG_FRIENDLY);
    unaggressive = QUERY_FLAG(op, FLAG_UNAGGRESSIVE);
    owner = object_get_owner(op);
    for (i = 0; i < op->stats.food; i++) {
        object *tmp;

        tmp = arch_to_object(op->other_arch);
        if (op->type == LAMP)
            tmp->stats.food = op->stats.food-1;
        tmp->stats.hp = op->stats.hp;
        if (friendly) {
            SET_FLAG(tmp, FLAG_FRIENDLY);
            add_friendly_object(tmp);
            tmp->attack_movement = PETMOVE;
            if (owner != NULL)
                object_set_owner(tmp, owner);
        }
        if (unaggressive)
            SET_FLAG(tmp, FLAG_UNAGGRESSIVE);
        if (env) {
            tmp->x = env->x,
            tmp->y = env->y;
            tmp = object_insert_in_ob(tmp, env);
        } else
            object_insert_to_free_spot_or_free(tmp, op->map, op->x, op->y, 1, SIZEOFFREE1+1, op);
    }
    if (friendly)
        remove_friendly_object(op);
    object_free_drop_inventory(op);
}
