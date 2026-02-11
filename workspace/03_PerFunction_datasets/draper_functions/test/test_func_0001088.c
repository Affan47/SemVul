BasicPush(int lev, int brack)


{

    diagnostics(6,"pushing rec=%d and bra=%d on  stack",lev,brack);
    ++top;
    stack[top] = lev;
    ++top;
    stack[top] = brack;

    if (top >= STACKSIZE)
        diagnostics(ERROR, "Nesting too deep.  latex2rtf bug, if file TeXs properly");

    return top;
}
