pathx_symtab_undefine(struct pathx_symtab **symtab, const char *name) {
    struct pathx_symtab *del = NULL;

    for(del = *symtab;
        del != NULL && !STREQ(del->name, name);
        del = del->next);
    if (del == NULL)
        return 0;
    list_remove(del, *symtab);
    free_symtab(del);
    return 0;
}
