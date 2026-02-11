Itcl_GetStackValue(stack,pos)
    Itcl_Stack *stack;
    int pos;
{
    if (stack->values && (stack->len > 0)) {
        assert(pos < stack->len);
        return stack->values[pos];
    }
    return (ClientData)NULL;
}
