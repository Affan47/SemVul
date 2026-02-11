hit_with_arrow(object *op, object *victim) {
    object *container, *hitter;
    int hit_something = 0;
    tag_t victim_tag, hitter_tag;
    sint16 victim_x, victim_y;
    mapstruct *victim_map;
    const char *old_skill = NULL;


    hitter = op->inv;
    FOR_OB_AND_BELOW_PREPARE(hitter)
        if (hitter->type != EVENT_CONNECTOR) {
            break;
        }
    FOR_OB_AND_BELOW_FINISH();
    if (!hitter) {
        container = NULL;
        hitter = op;
        if (free_no_drop(hitter))
            return NULL;
    } else {
        container = op;
        object_remove(hitter);
        if (free_no_drop(hitter))
            return NULL;

        object_insert_in_map_at(hitter, container->map, hitter, INS_NO_MERGE|INS_NO_WALK_ON, container->x, container->y);


    }


    victim_x = victim->x;
    victim_y = victim->y;
    victim_map = victim->map;
    victim_tag = victim->count;
    hitter_tag = hitter->count;


    if (execute_event(op, EVENT_ATTACK, hitter, victim, NULL, SCRIPT_FIX_ALL) == 0) {


        if (container != NULL) {
            old_skill = hitter->skill;
            hitter->skill = add_refcount(container->skill);
        }
        hit_something = attack_ob_simple(victim, hitter, op->stats.dam, op->stats.wc);
    }


    if (object_was_destroyed(hitter, hitter_tag) || hitter->env != NULL) {
        if (container) {
            object_remove(container);
            object_free_drop_inventory(container);
        }
        return NULL;
    }
    if (container != NULL) {
        free_string(hitter->skill);
        hitter->skill = old_skill;
    }


    if (hit_something && op->speed <= 10.0) {

        if (container == NULL) {
            hitter = fix_stopped_arrow(hitter);
            if (hitter == NULL)
                return NULL;
        } else {
            object_remove(container);
            object_free_drop_inventory(container);
        }


        if (!object_was_destroyed(victim, victim_tag)
        && stick_arrow(hitter, victim))
            return NULL;


        if (victim_x != hitter->x || victim_y != hitter->y) {
            object_remove(hitter);
            object_insert_in_map_at(hitter, victim_map, hitter, 0, victim_x, victim_y);
        } else {

            object_merge(hitter, NULL);
        }
        return NULL;
    }

    if (hit_something && op->speed >= 10.0)
        op->speed -= 1.0;


    if (container) {
        object_remove(hitter);
        object_insert_in_ob(hitter, container);
    }
    return op;
}
