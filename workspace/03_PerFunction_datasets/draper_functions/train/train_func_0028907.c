PushState(HandlerStateEnum eVal)
{
    if (nStackDepth + 1 == STACK_SIZE)
    {
        bStopParsing = TRUE;
        return;
    }
    nStackDepth ++;
    stateStack[nStackDepth].eVal = eVal;
    stateStack[nStackDepth].nBeginDepth = nDepth;
}
