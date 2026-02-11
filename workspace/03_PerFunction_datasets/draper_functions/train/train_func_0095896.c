FuncSMALLEST_FIELD_VECFFE( Obj self, Obj vec)
{
  Obj elm;
  UInt deg,deg1,deg2,i,len,p,q;
  UInt isVecFFE =IsVecFFE(vec);
  len  = LEN_PLIST(vec);
  if (len == 0)
    return Fail;
  elm = ELM_PLIST(vec,1);
  if (!isVecFFE && !IS_FFE(elm))
    return Fail;
  deg = DegreeFFE(elm);
  p = CharFFE(elm);
  for (i = 2; i <= len; i++)
    {
      elm =ELM_PLIST(vec,i);
      if (!isVecFFE && (!IS_FFE(elm)|| CharFFE(elm) != p))
	return Fail;
      deg2 =  DegreeFFE(elm);
      deg1 = deg;
      while (deg % deg2 != 0)
	deg += deg1;
    }
  q = p;
  for (i = 2; i <= deg; i++)
    q *= p;
  return INTOBJ_INT(q);
}
