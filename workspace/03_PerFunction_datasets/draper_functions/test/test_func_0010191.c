CreateTclThread(NsInterp *itPtr, char *script, int detached, Ns_Thread *thrPtr)
{
    ThreadArg *argPtr;

    argPtr = ns_malloc(sizeof(ThreadArg) + strlen(script));
    argPtr->detached = detached;
    strcpy(argPtr->script, script);
    argPtr->server = (itPtr ? itPtr->servPtr->server : NULL);
    Ns_ThreadCreate(NsTclThread, argPtr, 0, thrPtr);
}
