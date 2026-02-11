gwy_module_foreach(GHFunc function,
                   gpointer data)
{
    GwyModuleForeachData fdata;

    g_return_if_fail(modules_initialized);

    fdata.data = data;
    fdata.func = function;
    g_hash_table_foreach(modules, (GHFunc)gwy_module_foreach_one, &fdata);
}
