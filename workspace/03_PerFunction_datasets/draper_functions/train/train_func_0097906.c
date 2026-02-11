reload_int(int reload, Octstr *desc, long *o, long *n)
{
    if (reload && *o != *n) {
        info(0, "Reloading int '%s' from %ld to %ld",
             octstr_get_cstr(desc), *o, *n);
        *o = *n;
    }
}
