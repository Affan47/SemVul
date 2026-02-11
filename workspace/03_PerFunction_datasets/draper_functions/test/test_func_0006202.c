find_related(word w)
{
  int i;
  int item;

  if (w==0) return 0;
  item=0;
  nounloop(i)
    if (noun[i].name==w) {
      if (visible(i+first_noun)) return i+first_noun;
      else if (item==0) item=i+first_noun;
    }
  creatloop(i)
    if (creature[i].name==w) {
      if (visible(i+first_creat)) return i+first_creat;
      else if (item==0) item=i+first_creat;
    }
  return item;
}
