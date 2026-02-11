fix_array_shapes(List *arg_list,
                 Module_table *new_module)
{
    List *li;
    Argument *arg;

    for (li = arg_list; li != NULL; li = li->next) {
        arg = li->data;
        if (operand_kind(arg->formal) == KIND_ARRAY) {
            fix_array_shape(arg_list, new_module, arg);
        }
    }
}
