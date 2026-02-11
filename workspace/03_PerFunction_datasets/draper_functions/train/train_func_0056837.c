append_child()
{
  Zone empty;
  empty.ztype = ztype;
  empty.text_start = 0;
  empty.text_length = 0;
  empty.zone_parent=this;
  children.append(empty);
  return & children[children.lastpos()];
}
