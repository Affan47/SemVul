pushWSPixel(L_HEAP   *lh,
            L_STACK  *stack,
            l_int32   val,
            l_int32   x,
            l_int32   y,
            l_int32   index)
{
L_WSPIXEL  *wsp;

    PROCNAME("pushWSPixel");

    if (!lh) {
        L_ERROR("heap not defined\n", procName);
        return;
    }
    if (!stack) {
        L_ERROR("stack not defined\n", procName);
        return;
    }


    if (lstackGetCount(stack) > 0)
        wsp = (L_WSPIXEL *)lstackRemove(stack);
    else
        wsp = (L_WSPIXEL *)CALLOC(1, sizeof(L_WSPIXEL));

    wsp->val = (l_float32)val;
    wsp->x = x;
    wsp->y = y;
    wsp->index = index;
    lheapAdd(lh, wsp);
    return;
}
