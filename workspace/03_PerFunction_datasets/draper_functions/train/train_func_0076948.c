AddNodeMedianList(MedianPixelList *pixel_list,
                              const unsigned int channel,
                              const unsigned int color)
{
  register MedianSkipList
    *list;

  register int
    level;

  unsigned int
    search,
    update[9];


  list=pixel_list->lists+channel;
  list->nodes[color].signature=pixel_list->signature;
  list->nodes[color].count=1;


  search=65536UL;
  for (level=list->level; level >= 0; level--)
    {
      while (list->nodes[search].next[level] < color)
        search=list->nodes[search].next[level];
      update[level]=search;
    }


  for (level=0; ; level++)
    {
      pixel_list->seed=(pixel_list->seed*42893621U)+1U;
      if ((pixel_list->seed & 0x300) != 0x300)
        break;
    }
  if (level > 8)
    level=8;
  if (level > (list->level+2))
    level=list->level+2;


  while (level > list->level)
    {
      list->level++;
      update[list->level]=65536U;
    }


  do
    {
      list->nodes[color].next[level]=list->nodes[update[level]].next[level];
      list->nodes[update[level]].next[level]=color;
    }
  while (level-- > 0);
}
