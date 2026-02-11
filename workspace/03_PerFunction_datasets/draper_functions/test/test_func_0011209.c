convert_to_all(parse_rec *list, int *ofsref)
{
  int i;
  int cnt;

  for(i=*ofsref;list[i].info!=D_AND && list[i].info!=D_END;i++);
  cnt=i-*ofsref;

  while(list[i].info!=D_END) i++;
  list=rrealloc(list,(i+cnt)*sizeof(parse_rec));
  memmove(list+*ofsref+2*cnt-1,list+*ofsref+cnt,
	  (i+1-cnt-*ofsref)*sizeof(parse_rec));
  for(i=cnt-1;i>=0;i--) {
    int k;
    list[*ofsref+2*i]=list[*ofsref+i];
    if (i==0) break;
    k=*ofsref+2*i-1;
    list[k].obj=0;
    list[k].num=0;
    list[k].adj=list[k].noun=0;
    list[k].info=D_AND;
  }

  return list;
}
