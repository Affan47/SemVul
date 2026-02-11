remove_locked_door(object *op) {
    int i;
    object *tmp;

    for (i = 1; i < 9; i += 2) {
        tmp = map_find_by_type(op->map, op->x+freearr_x[i], op->y+freearr_y[i], LOCKED_DOOR);
        if (tmp && tmp->slaying == op->slaying) {
            tmp->speed = 0.1;
            object_update_speed(tmp);
            tmp->speed_left = -0.2;
        }
    }
    if (op->other_arch) {
        tmp = arch_to_object(op->other_arch);
        tmp->level = op->level;
        object_insert_in_map_at(tmp, op->map, op, 0, op->x, op->y);
    }
    object_remove(op);
    object_free_drop_inventory(op);
}
