object_get_player_container(object *op) {
    for (; op != NULL && op->type != PLAYER; op = op->env)

        if (op->env == op)
            op->env = NULL;
    return op;
}
