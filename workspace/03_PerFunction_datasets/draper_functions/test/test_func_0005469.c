symtab_remove_by_type(symbol_type type)
{
    int i;

    symbol_ident_list list;

    int count = symtab_list_type(type, &list);

    for (i=0; i<count; i++) {
        symtab_remove(list.idents[i]);
    }

    symtab_list_finalize(&list);
}
