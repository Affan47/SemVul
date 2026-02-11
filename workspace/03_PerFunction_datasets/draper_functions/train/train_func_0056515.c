FuncADD_ROW_VECTOR_3_FAST ( Obj self,
                                Obj list1,
                                Obj list2,
                                Obj mult )
{
  UInt i;
  Obj e1,e2, prd, sum;
  UInt len = LEN_PLIST(list1);
  if (LEN_PLIST(list2) != len)
    {
      list2 = ErrorReturnObj("AddRowVector: lists must be the same length",
                             0L, 0L,
                             "you can replace second list <list2> via 'return <list2>;'");
      return CALL_3ARGS(AddRowVectorOp, list1, list2, mult);
    }

  for (i = 1; i <= len; i++)
    {
      e1 = ELM_PLIST(list1,i);
      e2 = ELM_PLIST(list2,i);
      if ( !ARE_INTOBJS( e2, mult ) || !PROD_INTOBJS( prd, e2, mult ))
        {
          prd = PROD(e2,mult);
        }
      if ( !ARE_INTOBJS(e1, prd) || !SUM_INTOBJS( sum, e1, prd) )
        {
          sum = SUM(e1,prd);
          SET_ELM_PLIST(list1,i,sum);
          CHANGED_BAG(list1);
        }
      else
          SET_ELM_PLIST(list1,i,sum);
    }
  return 0;
}
