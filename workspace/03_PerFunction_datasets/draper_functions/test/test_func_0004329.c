quick_call_sfun(object fun)
{ DEBUG_AVMA
  int i=fun->sfn.sfn_argd,n=SFUN_NARGS(i);
  enum ftype restype;
  object *x,res,*base;
  object *temp_ar=alloca(n*sizeof(object));


  base = vs_base;
  if (n != vs_top - base)
    {check_arg_failed(n);}
  restype = SFUN_RETURN_TYPE(i);
  SFUN_START_ARG_TYPES(i);

#define COERCE_ARG(a,type)  (type==f_object ? a : (object)(fix(a)))
  if (i==0)
    x=vs_base;
  else
    {int j;
     x=temp_ar;
     for (j=0; j<n ; j++)
       {enum ftype typ=SFUN_NEXT_TYPE(i);
	x[j]=COERCE_ARG(vs_base[j],typ);}}
  SET_TO_APPLY(res,fun->sfn.sfn_self,n,x);
  base[0]=
    (restype==f_object ?  res :
     restype==f_fixnum ? make_fixnum((long)res)
     :(object) (FEerror("Bad result type",0),Cnil));
  vs_base = base;
  vs_top=base+1;
  CHECK_AVMA;
  return;}
