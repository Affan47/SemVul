cfapi_object_say(int *type, ...) {
    object *op;
    char *msg;
    va_list args;
    int *rint;
    char empty[] = "";

    va_start(args, type);
    op = va_arg(args, object *);
    msg = va_arg(args, char *);
    rint = va_arg(args, int *);
    va_end(args);

    if (op->type == PLAYER) {
        command_say(op, msg == NULL ? empty  : msg);
    } else {
        monster_npc_say(op, msg);
    }
    *rint = 0;
    *type = CFAPI_INT;
}
