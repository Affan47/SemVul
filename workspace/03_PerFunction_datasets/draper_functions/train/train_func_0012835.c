make_object_glow(object *op, int radius, int time) {
    object *tmp;


    if (op->path_denied&PATH_LIGHT)
        return 0;

    tmp = create_archetype(FORCE_NAME);
    tmp->speed = 0.01;
    tmp->stats.food = time;
    SET_FLAG(tmp, FLAG_IS_USED_UP);
    tmp->glow_radius = radius;
    if (tmp->glow_radius > MAX_LIGHT_RADII)
        tmp->glow_radius = MAX_LIGHT_RADII;

    tmp->x = op->x;
    tmp->y = op->y;
    if (tmp->speed < MIN_ACTIVE_SPEED)
        tmp->speed = MIN_ACTIVE_SPEED;
    tmp = object_insert_in_ob(tmp, op);
    if (tmp->glow_radius > op->glow_radius)
        op->glow_radius = tmp->glow_radius;

    if (!tmp->env || op != tmp->env) {
        LOG(llevError, "make_object_glow() failed to insert glowing force in %s\n", op->name);
        return 0;
    }
    return 1;
}
