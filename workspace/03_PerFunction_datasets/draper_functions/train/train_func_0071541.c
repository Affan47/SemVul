handle_save_command(String *args, int offset)
{
    if (restriction >= RESTRICT_FILE) {
        eprintf("restricted");
        return shareval(val_zero);
    }
    if (args->len - offset) return newint(save_macros(args, offset));
    eprintf("missing filename");
    return shareval(val_zero);
}
