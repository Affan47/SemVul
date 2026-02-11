do_skill_detect_curse(object *pl, object *skill) {
    int success = 0;

    FOR_INV_PREPARE(pl, tmp)
        if (!tmp->invisible) success += detect_curse_on_item(pl, tmp, skill);
    FOR_INV_FINISH();


    FOR_MAP_PREPARE(pl->map, pl->x, pl->y, tmp)
        if (object_can_pick(pl, tmp) || QUERY_FLAG(tmp, FLAG_IS_CAULDRON))
            success += detect_curse_on_item(pl, tmp, skill);
    FOR_MAP_FINISH();

    return success;
}
