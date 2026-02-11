acl_hash_entry_destroy(Symbol_t * sym, void * argp)
{
    if (sym != 0) {


        if (sym->sym_name != 0) {
            PERM_FREE(sym->sym_name);
        }


        PERM_FREE(sym);
    }


    return SYMENUMREMOVE;
}
