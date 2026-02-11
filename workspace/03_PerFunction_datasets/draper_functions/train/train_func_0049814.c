Gen_To_Cpx(Gen_node g){
  fcomplex c;
  if (g==0)  bad_error("NULL arg to Gen_To_Cpx\n");
  switch (g->type){
     case Int_T: c=ItoC(g->Genval.ival);
                 break;
     case Dbl_T: c=DtoC(g->Genval.dval);
                 break;
     case Cpx_T: c=g->Genval.cval;
                 break;
        default: bad_error("Don't know how to coerce in Gen_To_Cpx\n");
                 break;
  }
  return c;
}
