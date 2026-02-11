gonzo_project_list(string_list_ty *result)
{
    size_t          n;
    size_t          j;
    gonzo_ty        *gp;
    gstate_ty       *gstate_data;

    trace(("gonzo_project_list(result = %08lX)\n{\n", (long)result));
    result->clear();
    for (n = 0;; ++n)
    {
        gp = gonzo_nth(n);
        if (!gp)
            break;


        gstate_data = gonzo_gstate_get(gp);


        assert(gstate_data->where);
        for (j = 0; j < gstate_data->where->length; ++j)
        {
            gstate_where_ty *addr;

            addr = gstate_data->where->list[j];
            if (addr->alias_for)
                continue;
            result->push_back_unique(addr->project_name);
        }
    }
    trace(("}\n"));
}
