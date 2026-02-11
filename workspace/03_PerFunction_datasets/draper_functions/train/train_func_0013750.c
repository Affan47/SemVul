spifconf_register_builtin(char *name, spifconf_func_ptr_t ptr)
{
    ASSERT_RVAL(!SPIF_PTR_ISNULL(name), SPIF_CAST_C(unsigned char) -1);

    builtins[builtin_idx].name = SPIF_CAST(charptr) STRDUP(name);
    builtins[builtin_idx].ptr = ptr;
    if (++builtin_idx == builtin_cnt) {
        builtin_cnt *= 2;
        builtins = (spifconf_func_t *) REALLOC(builtins, sizeof(spifconf_func_t) * builtin_cnt);
    }
    return (builtin_idx - 1);
}
