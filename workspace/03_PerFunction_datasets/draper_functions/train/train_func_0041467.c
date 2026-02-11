readformat(strom,tokptr)
truc *strom;
int *tokptr;
{
    truc *arr;
    truc obj;
    int m = 0;

    arr = workStkPtr + 1;
    while(*tokptr == COLONTOK) {
        nexttok(strom,1);
        obj = readexpr(strom,0);
        if(obj == parserrsym)
            goto cleanup;
        WORKpush(obj);
        m++;
        *tokptr = skipeoltok(strom);
    }
    obj = mkntuple(fTUPLE,arr,m);
  cleanup:
    workStkPtr = arr - 1;
    return(obj);
}
