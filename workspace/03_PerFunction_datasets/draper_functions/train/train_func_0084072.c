validate_index(astnode *n, void *arg, astnode **next)
{
    symtab_entry *e;
    astnode *id;
    astnode *type;
    if (is_field_ref(LHS(n))) {
        return 1;
    }
    id = LHS(n);
    if (!astnode_is_type(id, IDENTIFIER_NODE)) {
        err(n->loc, "identifier expected");
        astnode_replace(n, astnode_create_integer(0, n->loc) );
        astnode_finalize(n);
        return 0;
    }
    e = symtab_lookup(id->ident);
    if (e != NULL) {
        type = LHS(e->def);
        if (!astnode_is_type(type, DATATYPE_NODE)) {
            err(n->loc, "`%s' cannot be indexed", id->ident);
            astnode_replace(n, astnode_create_integer(0, n->loc) );
            astnode_finalize(n);
            return 0;
        } else {

            astnode *reduced = reduce_index(n);
            if (reduced != n) {
                *next = reduced;
                return 0;
            }
        }
    } else {
        err(n->loc, "unknown symbol `%s'", id->ident);
        astnode_replace(n, astnode_create_integer(0, n->loc) );
        astnode_finalize(n);
        return 0;
    }
    return 1;
}
