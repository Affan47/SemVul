doneCB(V v_,A d_,A i_,A p_)
{
  AFunction *doneFunc=getDoneFunc(v_);
  if (doneFunc!=0)
    {
      doneFunc->execute(v_,(d_!=0)?(A)ic(d_):d_,
			(i_!=0)?(A)ic(i_):i_,(p_!=0)?(A)ic(p_):p_);
      if (d_!=0) dc(d_);
      if (i_!=0) dc(i_);
      if (p_!=0) dc(p_);
    }
}
