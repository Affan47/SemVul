cfapi_generate_random_map(int *type, ...) {
    va_list args;
    const char *name;
    RMParms *rp;
    char **use_layout;
    mapstruct **ret;

    va_start(args, type);
    name = va_arg(args, const char *);
    rp = va_arg(args, RMParms *);
    use_layout = va_arg(args, char **);
    ret = va_arg(args, mapstruct **);
    va_end(args);

    *ret = generate_random_map(name, rp, use_layout);
}
