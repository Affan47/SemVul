on_canvas_drag_leave(const Glib::RefPtr<Gdk::DragContext>& , guint )
{


  if(m_layout_item_dropping)
  {
    m_layout_item_dropping->remove();
    m_layout_item_dropping.reset();
  }

  m_canvas.show_temp_rule(0, 0, false);
}
