context_pop(context_t *ctx)
{
    stack_elem_t *stack;
    yajl_val v;

    if (ctx->stack == NULL)
        RETURN_ERROR (ctx, NULL, "context_pop: "
                      "Bottom of stack reached prematurely");

    stack = ctx->stack;
    ctx->stack = stack->next;

    v = stack->value;

    free (stack);

    return (v);
}
