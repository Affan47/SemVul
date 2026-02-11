get_adep(Block *src,
         Block *dst,
         dep_type type,
         Array_def_use_table_semnode *du)
{
    Adep *adep;

    if (du == NULL) {
        return NULL;
    }

    adep = zcalloc(1, sizeof(Adep));

    adep->type = type;
    adep->entry = du->entry;
    adep->du = du;
    adep->src = src;
    adep->dst = dst;

    adep->sched_time = -1.0;

    return adep;
}
