stmt_if_alloc(blob_list_ty *condition, stmt_ty *then_clause,
    stmt_ty *else_clause)
{
    stmt_if_ty      *result;
    blob_list_ty    *c2;
    table_ty        *tp;

    trace(("stmt_if_alloc()\n{\n"));
    result = (stmt_if_ty *)stmt_alloc(&method);

    assert(condition->length >= 1);
    for (tp = table; tp < ENDOF(table); ++tp)
    {
        if (!tp->fast)
            tp->fast = str_from_c(tp->name);
        if (str_equal(condition->list[0]->text, tp->fast))
            break;
    }
    assert(tp < ENDOF(table));
    if (tp >= ENDOF(table))
        tp = &table[0];
    c2 = tp->rewrite(condition, &result->ref);
    blob_list_free(condition);

    result->condition = c2;
    result->then_clause = then_clause;
    result->else_clause = else_clause;

    stmt_variable_merge((stmt_ty *)result, then_clause);
    if (else_clause)
        stmt_variable_merge((stmt_ty *)result, else_clause);
    trace(("}\n"));
    return (stmt_ty *)result;
}
