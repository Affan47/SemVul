enter_struc_union_field(astnode *n, astnode *offset, ordered_field_list ***plist, astnode *struc_id)
{
    ordered_field_list *ls;
    symtab_entry *se;
    symtab_entry *fe;
    static int id = 0;
    char id_str[16];
    astnode *union_id;
    union_id = LHS(n);
    if (astnode_is_type(union_id, IDENTIFIER_NODE)) {
        err(n->loc, "anonymous union expected");
        return(offset);
    }
    snprintf(id_str, sizeof (id_str), "%d", id++);
    se = symtab_enter(id_str, UNION_SYMBOL, n, 0);
    enter_union_fields(se, n);

    (**plist) = malloc(sizeof(ordered_field_list));
    (**plist)->entry = se;
    (**plist)->next = NULL;
    *plist = &((**plist)->next);

    for (ls = se->struc.fields; ls != NULL; ls = ls->next) {

        fe = symtab_enter(
            ls->entry->id,
            VAR_SYMBOL,
            astnode_clone(ls->entry->def, ls->entry->def->loc),
            0
        );
        if (fe == NULL) {
            err(ls->entry->def->loc, "duplicate symbol `%s' in structure `%s'", ls->entry->id, struc_id->ident);
            continue;
        }

        fe->field.offset = astnode_clone(offset, offset->loc);

        fe->field.size = astnode_clone(se->struc.size, offset->loc);
    }

    offset = astnode_create_arithmetic(
        PLUS_OPERATOR,
        offset,
        astnode_clone(se->struc.size, offset->loc),
        offset->loc
    );
    offset = reduce_expression(offset);
    return(offset);
}
