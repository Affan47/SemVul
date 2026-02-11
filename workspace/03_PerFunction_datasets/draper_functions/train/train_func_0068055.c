entry_is_listent(long int lineno)
{
    register AddrScrn_Disp *dl;

    if((dl = dlist(lineno)) && dl->type == ListEnt)
      return 1;

    return 0;
}
