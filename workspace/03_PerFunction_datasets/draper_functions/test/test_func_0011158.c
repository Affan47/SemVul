transfer_ob(object *op, int x, int y, int randomly, object *originator) {
    int i;
    object *tmp;

    if (randomly)
        i = object_find_free_spot(op, op->map, x, y, 0, SIZEOFFREE);
    else
        i = object_find_first_free_spot(op, op->map, x, y);

    if (i == -1)
        return 0;

    op = HEAD(op);
    object_remove(op);
    tmp = object_insert_in_map_at(op, op->map, originator, 0, x+freearr_x[i], y+freearr_y[i]);
    if (op && op->type == PLAYER)
        map_newmap_cmd(&op->contr->socket);
    if (tmp)
        return 0;
    else
        return 1;
}
