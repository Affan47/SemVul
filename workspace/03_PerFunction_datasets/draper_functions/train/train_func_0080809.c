GetNonpeakMedianList(MedianPixelList *pixel_list)
{
  PixelPacket
    pixel;

  register MedianSkipList
    *list;

  register long
    channel;

  unsigned long
    channels[4],
    center,
    color,
    count,
    previous,
    next;


  center=pixel_list->center;
  for (channel=0; channel < 4; channel++)
  {
    list=pixel_list->lists+channel;
    color=65536L;
    next=list->nodes[color].next[0];
    count=0;
    do
    {
      previous=color;
      color=next;
      next=list->nodes[color].next[0];
      count+=list->nodes[color].count;
    }
    while (count <= center);
    if ((previous == 65536L) && (next != 65536L))
      color=next;
    else
      if ((previous != 65536L) && (next == 65536L))
        color=previous;
    channels[channel]=color;
  }
  pixel.red=ScaleShortToQuantum(channels[0]);
  pixel.green=ScaleShortToQuantum(channels[1]);
  pixel.blue=ScaleShortToQuantum(channels[2]);
  pixel.opacity=ScaleShortToQuantum(channels[3]);
  return(pixel);
}
