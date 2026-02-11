Cudd_zddShuffleHeap(
  DdManager * table ,
  int * permutation )
{

    int	result;

    empty = table->zero;
    zddReorderPreprocess(table);

    result = zddShuffle(table,permutation);

    if (!zddReorderPostprocess(table)) return(0);

    return(result);

}
