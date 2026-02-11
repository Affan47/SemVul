gncTaxTableAddChild (GncTaxTable *table, GncTaxTable *child)
{
    g_return_if_fail(table);
    g_return_if_fail(child);
    g_return_if_fail(qof_instance_get_destroying(table) == FALSE);

    table->children = g_list_prepend(table->children, child);
}
