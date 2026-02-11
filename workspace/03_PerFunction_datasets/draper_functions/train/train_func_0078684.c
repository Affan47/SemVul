MinMax(const RN_& U,const RN_& V,int i0,int i1) const
{
  R2 minmax(1e100,-1e100);
  int nsb = nbsubdivision();
  int nsb2 =  NbOfSubTriangle(nsb);
  int nbdf=NbDoF();
  RN fk(nbdf);
  RN gk(nbdf);
  RNMK fb(nbdf,N,3);
  RN f0(3);
  RN f1(3);
  bool whatd[last_operatortype];
  initwhatd(whatd,0);
  R2 Pt,A(T[0]),B(T[1]),C(T[2]);
  for (int i=0;i<nbdf;i++)
    fk[i] = U[operator()(i)];
  for (int i=0;i<nbdf;i++)
    gk[i] = V[operator()(i)];
  for (int k=0;k<nsb2;k++)
   {

     for (int j=0;j<3;j++)
      {

        R2 Pt=SubTriangle(nsb,k,j);
        BF(whatd,Pt,fb);
        f0[j] = (fb('.',i0,0),fk);
        f1[j] = (fb('.',i1,0),gk);
        R2 uv(f0[j],f1[j]);
        R uv2 = (uv,uv);
        minmax.x=Min(minmax.x,uv2);
        minmax.y=Max(minmax.y,uv2);

       }
    }
   return minmax;
}
