divMPP(polynomial1 mi, polynomial1 P1, polynomial1 P2)
{
  polynomial1 p,m=mi;
  int i,free_m=0;

  if (P1==0||m==0) { if (P2!=0) freeP(P2);
                      return 0;}
  if (P1->R!=m->R){ printf("Rings must be equal in divMPP");
                   if (P2!=0) freeP(P2);
                          return 0;}
  if (m->next!=0){ printf("divisor must be a monomial in divMPP");
                   if (P2!=0) freeP(P2);
                    return 0;}

  if (P2==m) free_m = 1;
  if (P2!=P1 ) { if ( P2 !=0 && P2 !=m)  freeP(P2);
                 P2=copyP(P1);}
  p=P2;
  while (p!=0){
    p->coef=Cdiv(p->coef,m->coef);
    p->def-=m->def;
    for(i=0;i<m->R->n;i++) p->exps[i]-=m->exps[i];
    p=p->next;
  }
 if (free_m==1) freeP(m);
 return P2;
}
