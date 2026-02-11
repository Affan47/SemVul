nextVisible(TreeMapItem* i)
{
  TreeMapItem* p = i->parent();
  if (!p || p->itemRect().isEmpty()) return -1;

  int idx = p->children()->indexOf(i);
  if (idx<0) return -1;

  while (idx < (int)p->children()->count()-1) {
    idx++;
    QRect r = p->children()->at(idx)->itemRect();
    if (r.width()>1 && r.height()>1)
      return idx;
  }
  return -1;
}
