AddTimes(expr_t iArg1, expr_t iArg2)
{
  if (iArg1 == MinusOne)
    return AddUMinus(iArg2);
  else if (iArg2 == MinusOne)
    return AddUMinus(iArg1);
  else if (iArg1 != Zero && iArg1 != One && iArg2 != Zero && iArg2 != One)
    {


      if (iArg1->idx > iArg2->idx)
        {
          expr_t tmp = iArg1;
          iArg1 = iArg2;
          iArg2 = tmp;
        }
      return AddBinaryOp(iArg1, oTimes, iArg2);
    }
  else if (iArg1 != Zero && iArg1 != One && iArg2 == One)
    return iArg1;
  else if (iArg2 != Zero && iArg2 != One && iArg1 == One)
    return iArg2;
  else if (iArg2 == One && iArg1 == One)
    return One;
  else
    return Zero;
}
