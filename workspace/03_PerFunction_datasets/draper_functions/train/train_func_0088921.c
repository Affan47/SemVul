deletevar(vari* v)
{
    if (v == NULL)
    {
        fprintf(stderr, "Error: attempting to clear entire table through NULL delete\n");
        return;
    }

    VarTable::iterator i = var_table.find(v->name);
    if (i != var_table.end())
    {
        if (i->second && i->second->stat != STSYSPEC)
        {
            free(i->second->dpr);
        }
        free(i->second);
        var_table.erase(i);
    }
}
