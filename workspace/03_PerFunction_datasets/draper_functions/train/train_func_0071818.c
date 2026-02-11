antlr3StackNew	(ANTLR3_UINT32 sizeHint)
{
    pANTLR3_STACK   stack;


    stack    = (pANTLR3_STACK)ANTLR3_MALLOC((size_t)sizeof(ANTLR3_STACK));

    if	(stack == NULL)
    {
	return	(pANTLR3_STACK)ANTLR3_FUNC_PTR(ANTLR3_ERR_NOMEM);
    }


    stack->vector   = antlr3VectorNew(sizeHint);
    stack->top	    = NULL;

    if	(stack->vector == (pANTLR3_VECTOR)ANTLR3_FUNC_PTR(ANTLR3_ERR_NOMEM))
    {
	return	(pANTLR3_STACK)ANTLR3_FUNC_PTR(ANTLR3_ERR_NOMEM);
    }


    stack->get	=  antlr3StackGet;
    stack->free	=  antlr3StackFree;
    stack->pop	=  antlr3StackPop;
    stack->push	=  antlr3StackPush;
    stack->size	=  antlr3StackSize;
    stack->peek	=  antlr3StackPeek;

    return  stack;
}
