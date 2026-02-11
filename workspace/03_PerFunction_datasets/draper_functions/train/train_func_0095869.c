entry_is_addkey(long int lineno)
{
    register AddrScrn_Disp *dl;

    if((dl = dlist(lineno)) && (dl->type == AddFirstPers ||
                                dl->type == AddFirstGlob ||
                                dl->type == AskServer))
      return 1;

    return 0;
}
