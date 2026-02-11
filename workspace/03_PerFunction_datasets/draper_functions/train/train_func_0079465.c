StkTop(struct Stack *Stack)
{
    if (Stack && (Stack->Used > 0))
        return (Stack->Data[Stack->Used - 1]);
    else
        return (NULL);
}
