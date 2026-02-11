replace_strings(REPLACE *rep, char **start, uint *max_length,
                            char *from)
{
  reg1 REPLACE *rep_pos;
  reg2 REPLACE_STRING *rep_str;
  char *to, *end, *pos, *new;

  end=(to= *start) + *max_length-1;
  rep_pos=rep+1;
  for(;;)
  {
    while (!rep_pos->found)
    {
      rep_pos= rep_pos->next[(uchar) *from];
      if (to == end)
      {
	(*max_length)+=8192;
	if (!(new=my_realloc(*start,*max_length,MYF(MY_WME))))
	  return (uint) -1;
	to=new+(to - *start);
	end=(*start=new)+ *max_length-1;
      }
      *to++= *from++;
    }
    if (!(rep_str = ((REPLACE_STRING*) rep_pos))->replace_string)
      return (uint) (to - *start)-1;
    updated=1;
    to-=rep_str->to_offset;
    for (pos=rep_str->replace_string; *pos ; pos++)
    {
      if (to == end)
      {
	(*max_length)*=2;
	if (!(new=my_realloc(*start,*max_length,MYF(MY_WME))))
	  return (uint) -1;
	to=new+(to - *start);
	end=(*start=new)+ *max_length-1;
      }
      *to++= *pos;
    }
    if (!*(from-=rep_str->from_offset) && rep_pos->found != 2)
      return (uint) (to - *start);
    rep_pos=rep;
  }
}
