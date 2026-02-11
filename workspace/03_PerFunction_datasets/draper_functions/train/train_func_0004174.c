cmp_variant_op(const void *data, const void *arg)
{
    const Variant *v = data;
    const Operand *op = arg;

    if (semtree_symbol_kind(v->semtree) == op->kind
        && semtree_symbol_entry(v->semtree) == op->entry)
        return 0;
    else
        return 1;
}
