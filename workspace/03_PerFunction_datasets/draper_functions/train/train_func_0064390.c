handle_unbind_command(String *args, int offset)
{
    Macro *macro;

    if (!(args->len - offset)) return shareval(val_zero);
    if ((macro = find_key(print_to_ascii(NULL, args->data + offset)->data)))
        kill_macro(macro);
    else eprintf("No binding for %s", args->data + offset);
    return newint(!!macro);
}
