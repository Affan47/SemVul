get_pass_header(pool *p, const char **arg, array_header **array)
{
    const char **header;

    if (!*array) {
        *array = ap_make_array(p, 10, sizeof(char*));
    }

    header = (const char **)ap_push_array(*array);
    *header = ap_getword_conf(p, arg);

    return header ? NULL : "\"\"";
}
