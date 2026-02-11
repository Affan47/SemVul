free_symtab(struct pathx_symtab *symtab) {

    while (symtab != NULL) {
        struct pathx_symtab *del = symtab;
        symtab = del->next;
        free(del->name);
        release_value(del->value);
        free(del->value);
        free(del);
    }
}
