cgwop_destroy(struct cgwop *cgwop)
{
    int len;

    len = cgwop->num_fields;
    while (--len >= 0)
    {
        octstr_destroy(cgwop->name[len]);
        octstr_destroy(cgwop->value[len]);
    }

    gw_free(cgwop->name);
    gw_free(cgwop->value);
    gw_free(cgwop);
}
