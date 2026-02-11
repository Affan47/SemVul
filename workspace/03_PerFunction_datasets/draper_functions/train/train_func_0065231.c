Jim_StackPop(Jim_Stack *stack)
{
    if (stack->len == 0)
        return NULL;
    stack->len--;
    return stack->vector[stack->len];
}
