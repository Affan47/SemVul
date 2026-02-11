nextPage(float in_width,float in_height,NupPageEdit &ret)
{
  in_pages++;
  subpage++;
  if (subpage>=nup) {
    subpage=0;
    out_pages++;
  }

  ret.sub.width=in_width;
  ret.sub.height=in_height;

  auto sub=convert_order(subpage);
  calculate_edit(sub.first,sub.second,ret);

  return (subpage==0);
}
