assign_global_builtins(builtinspec_t *b)
{
    while (b->name != NULL) {
        setc(symbol(b->name), cbuiltin(b->name, b->fptr));
        b++;
    }
}
