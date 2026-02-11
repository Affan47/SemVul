reduce_mask(astnode *mask)
{
    symtab_entry *ns;
    symtab_entry *sym;
    astnode *c;
    astnode *namespace;
    astnode *symbol;
    astnode *expr;

    expr = LHS(mask);

    namespace = LHS(expr);
    ns = symtab_lookup(namespace->ident);
    if (ns != NULL) {

        if (ns->type != RECORD_SYMBOL) {
            err(expr->loc, "`%s' is not a record");

            c = astnode_create_integer(0, expr->loc);
            astnode_replace(mask, c);
            astnode_finalize(mask);
            expr = c;
        }
        else {

            symtab_push(ns->symtab);
            symbol = RHS(expr);
            sym = symtab_lookup(symbol->ident);
            if (sym != NULL) {


                c = astnode_create_arithmetic(
                    SHL_OPERATOR,
                    astnode_create_arithmetic(
                        MINUS_OPERATOR,
                        astnode_create_arithmetic(
                            SHL_OPERATOR,
                            astnode_create_integer(1, expr->loc),
                            astnode_clone(sym->field.size, expr->loc),
                            expr->loc
                            ),
                        astnode_create_integer(1, expr->loc),
                        expr->loc
                    ),
                    astnode_clone(sym->field.offset, expr->loc),
                    expr->loc
                );
                c = reduce_expression(c);
                astnode_replace(mask, c);
                astnode_finalize(mask);
                expr = c;
            }
            symtab_pop();
        }
    }
    return expr;
}
