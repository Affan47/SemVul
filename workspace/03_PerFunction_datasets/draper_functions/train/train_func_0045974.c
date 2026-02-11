remove_child(Gtk::Widget& child)
{


  if(child.is_managed_())
    child.reference();

  egg_spread_table_dnd_remove_child(gobj(), child.gobj());
}
