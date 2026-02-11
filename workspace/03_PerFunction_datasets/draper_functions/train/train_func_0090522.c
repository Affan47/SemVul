SpreadTableDnd(Gtk::Orientation orientation, guint lines)
:

  Glib::ObjectBase(0),
  SpreadTable(Glib::ConstructParams(spreadtable_class_.init(), "orientation", ((GtkOrientation)(orientation)), "lines", lines, static_cast<char*>(0)))
{
}
