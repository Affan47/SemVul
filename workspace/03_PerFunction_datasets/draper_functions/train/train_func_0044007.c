doMergeGrade(K a, I r, K x, K y, I s, I t)
{
  if(s >= t) R;
  I m=s+(t-s)/2;
  doMergeGrade(a,r,x,y,s,m);
  doMergeGrade(a,r,x,y,m+1,t);
  merger(a,r,x,y,s,t,m);
}
