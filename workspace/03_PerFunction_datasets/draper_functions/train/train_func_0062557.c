Common_Type(int t1, int t2){
  int temp;
  if (t1==t2)return t2;
  if (t1>t2){ temp=t2; t2=t1; t1=temp;}
  if (Is_Numeric(t1)==TRUE&&Is_Numeric(t2)==TRUE) return t2;
return INVALID_T;
}
