bondUnitVector(int bn, double& xv, double& yv) {


  double si,r1,r2,r3,s1,s2,s3,s4,x1,y1,y2;
  int na1,na2,i;

  na1=getBond(bn)->at[0];
  na2=getBond(bn)->at[1];
  s1=getAtom(na1)->rx;
  s2=getAtom(na1)->ry;
  s3=getAtom(na2)->rx;
  s4=getAtom(na2)->ry;
  r1=s1-s3;
  r2=s2-s4;
  r3=sqrt(r1*r1+r2*r2);
  r1=r1/r3;
  r2=r2/r3;
  si=0;
  for (i=0; i<getAtom(na1)->nb; i++) if (getAtom(na1)->ac[i] != na2) {
    x1=getAtom(getAtom(na1)->ac[i])->rx-s1;
    y1=getAtom(getAtom(na1)->ac[i])->ry-s2;
    y2=x1*r2-y1*r1;
    if (y2 != 0) si=si+y2/abs(y2);
  }
  for (i=0; i<getAtom(na2)->nb; i++) if (getAtom(na2)->ac[i] != na1) {
    x1=getAtom(getAtom(na2)->ac[i])->rx-s3;
    y1=getAtom(getAtom(na2)->ac[i])->ry-s4;
    y2=x1*r2-y1*r1;
    if (y2 != 0) si=si+y2/abs(y2);
  }
  if (si != 0) si=si/abs(si); else si=1;
  xv=-r2*si; yv=r1*si;
}
