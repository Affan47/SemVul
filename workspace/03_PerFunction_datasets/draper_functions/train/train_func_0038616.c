cfapi_object_apply(int *type, ...) {
    va_list args;
    object *applied;
    object *applier;
    int aflags;
    int *ret;

    va_start(args, type);

    applier = va_arg(args, object *);
    applied = va_arg(args, object *);
    aflags = va_arg(args, int);
    ret = va_arg(args, int *);

    va_end(args);

    *type = CFAPI_INT;
    *ret = apply_manual(applier, applied, aflags);
}
