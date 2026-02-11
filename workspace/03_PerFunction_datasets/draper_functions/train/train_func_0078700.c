getword(int item,int n)

{
  if (n==1) {
    if (item<0) return -item;
    else if (tnoun(item)) return noun[item-first_noun].adj;
    else if (tcreat(item)) return creature[item-first_creat].adj;
  }
  if (n==2)
    if (tnoun(item) || tcreat(item)) return it_name(item);
  return 0;
}
