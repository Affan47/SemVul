FuncGetPols(
                     Obj      self,
                     Obj      list,
                     Obj      pr,
                     Obj      pols      )
{
    if  (LEN_PLIST(list) != 4)
        ErrorReturnVoid("<list> must be a generalised representative not a tree"
                        ,0L, 0L, "you can 'return;'");
    GetPols(list, pr, pols);
    return (Obj) 0;
}
