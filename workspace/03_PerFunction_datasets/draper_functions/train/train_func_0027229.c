gonzo_project_delete_sub(gonzo_ty *gp, project_ty *pp)
{
    gstate_ty       *gstate_data;
    size_t          j;
    int             result;


    trace(("gonzo_project_delete_sub(gp = %08lX, pp = %08lX)\n{\n",
        (long)gp, (long)pp));
    gstate_data = gonzo_gstate_get(gp);
    assert(gstate_data->where);
    result = 0;
    for (j = 0; j < gstate_data->where->length; ++j)
    {
        gstate_where_ty *addr;
        size_t          k;

        addr = gstate_data->where->list[j];
        if (addr->alias_for)
            continue;
        if (!str_equal(addr->project_name, project_name_get(pp)))
            continue;


        for (k = j + 1; k < gstate_data->where->length; ++k)
            gstate_data->where->list[k - 1] = gstate_data->where->list[k];
        gstate_data->where->length--;


        gstate_where_type.free(addr);


        gp->modified = 1;
        result = 1;
        break;
    }
    trace(("return %d;\n", result));
    trace(("}\n"));
    return result;
}
