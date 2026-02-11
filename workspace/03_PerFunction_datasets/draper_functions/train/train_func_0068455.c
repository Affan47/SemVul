set_outlines_visibility(bool visible)
{

  m_outline_visibility = visible;


  Glib::RefPtr<Goocanvas::Item> root = m_items_group;
  if(!root)
    return;

  const int count = root->get_n_children();
  for(int i = 0; i < count; ++i)
  {
    Glib::RefPtr<Goocanvas::Item> child = root->get_child(i);
    Glib::RefPtr<CanvasLayoutItem> derived =
      Glib::RefPtr<CanvasLayoutItem>::cast_dynamic(child);
    if(!derived)
      continue;

    derived->set_outline_visible(visible);
  }
}
