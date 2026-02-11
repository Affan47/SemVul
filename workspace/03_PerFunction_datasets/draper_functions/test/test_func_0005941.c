object_find_first_free_spot(const object *ob, mapstruct *m, int x, int y) {
    int i;

    for (i = 0; i < SIZEOFFREE; i++) {
        if (!ob_blocked(ob, m, x+freearr_x[i], y+freearr_y[i]))
            return i;
    }
    return -1;
}
