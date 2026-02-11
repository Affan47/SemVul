destruct_modules_local_array(IntSet *func_local_array,
                             IntSet *subr_local_array)
{
    int funcmax = get_max_module_entry(MODULE_FUNC);
    int subrmax = get_max_module_entry(MODULE_SUB);

    int i;

    for (i = 0; i < funcmax + 1; i++) {
        if (func_local_array[i] != NULL) {
            destruct_IntSet(func_local_array[i]);
        }
    }
    for (i = 0; i < subrmax + 1; i++) {
        if (subr_local_array[i] != NULL) {
            destruct_IntSet(subr_local_array[i]);
        }
    }
}
