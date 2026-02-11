acl_sym_new(ACLHandle_t *acl)
{
    Symbol_t *sym;

    sym = (Symbol_t *) PERM_MALLOC(sizeof(Symbol_t));
    if ( sym == NULL )
        return(NULL);

    sym->sym_name = PERM_STRDUP(acl->tag);
    if ( sym->sym_name == NULL ) {
        PERM_FREE(sym);
        return(NULL);
    }

    sym->sym_type = ACLSYMACL;
    sym->sym_data = (void *) acl;
    return(sym);

}
