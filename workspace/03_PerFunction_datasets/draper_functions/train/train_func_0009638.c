reverse(IList<HtmlFOTBuilder::Item> &list)
{
  IList<HtmlFOTBuilder::Item> tem;
  while (!list.empty())
    tem.insert(list.get());
  tem.swap(list);
}
