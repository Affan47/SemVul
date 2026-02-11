cfapi_map_get_map(int *type, ...) {
    va_list args;
    mapstruct **ret;
    int ctype;
    int x, y;
    sint16 nx, ny;
    const char *name;
    mapstruct *m;

    va_start(args, type);

    ctype = va_arg(args, int);

    switch (ctype) {
    case 0:
        x = va_arg(args, int);
        y = va_arg(args, int);
        ret = va_arg(args, mapstruct **);
        *ret = get_empty_map(x, y);
        break;

    case 1:
        name = va_arg(args, const char *);
        x = va_arg(args, int);
        ret = va_arg(args, mapstruct **);
        *ret = ready_map_name(name, x);
        break;

    case 2:
        m = va_arg(args, mapstruct *);
        nx = va_arg(args, int);
        ny = va_arg(args, int);
        ret = va_arg(args, mapstruct **);
        *ret = get_map_from_coord(m, &nx, &ny);
        break;

    default:
        *type = CFAPI_NONE;
        va_end(args);
        return;
        break;
    }
    va_end(args);
    *type = CFAPI_PMAP;
}
