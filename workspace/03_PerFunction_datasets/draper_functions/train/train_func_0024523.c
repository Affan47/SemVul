_mesa_symbol_table_iterator_ctor(struct _mesa_symbol_table *table,
                                 int name_space, const char *name)
{
    struct _mesa_symbol_table_iterator *iter = calloc(1, sizeof(*iter));
    struct symbol_header *const hdr = find_symbol(table, name);

    iter->name_space = name_space;

    if (hdr != NULL) {
        struct symbol *sym;

        for (sym = hdr->symbols; sym != NULL; sym = sym->next_with_same_name) {
            assert(sym->hdr == hdr);

            if ((name_space == -1) || (sym->name_space == name_space)) {
                iter->curr = sym;
                break;
            }
        }
    }

    return iter;
}
