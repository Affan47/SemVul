leaf_reset(void)
{
    if (stp)
        symtab_free(stp);
    if (leaf_pattern)
        string_list_delete(leaf_pattern);
    if (interior_pattern)
        string_list_delete(interior_pattern);
    if (exterior_pattern)
        string_list_delete(exterior_pattern);
    if (leaf_file)
        string_list_delete(leaf_file);
    if (interior_file)
        string_list_delete(interior_file);
    if (exterior_file)
        string_list_delete(exterior_file);
    stp = 0;
    leaf_file = 0;
    leaf_pattern = 0;
    interior_file = 0;
    interior_pattern = 0;
    exterior_file = 0;
    exterior_pattern = 0;
}
