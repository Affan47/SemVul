Set_Ring(Gen_node g)
{
  Pring R;
  polynomial1 tp;
  int n=0;
  Gen_node pt,pt1;

  pt=g;

  while(pt!=0) {
    n++;
    pt=Gen_next(pt);
  }

  R=makePR(n-1);
  n=0;
  pt=g;
  while(n<ring_dim(R)) {
    tp=makeP(R);
    *poly_coef(tp)=Complex(1.0,0.0);
    *poly_exp(tp,n+1)=1;
    pt1=PLYND(tp);
    install(pt->Genval.idval,pt1);
    ring_set_var(R,n,Gen_idval(pt));
    n++;

    pt=Gen_next(pt);
  }

  tp=makeP(R);

  *poly_coef(tp)=Complex(1.0,0.0);

  *poly_def(tp)=1;
  pt1=PLYND(tp);

  install(pt->Genval.idval,pt1);

  ring_set_def(R,Gen_idval(pt));


  free_Gen_list(g);

  Def_Ring=R;
  N=ring_dim(R);

  return IDND("You have tried to print the Gen_node containing  the Default Ring");
}
