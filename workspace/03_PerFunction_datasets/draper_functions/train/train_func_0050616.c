get_selected_treeview()
{
  switch(m_notebook_parts->get_current_page())
  {


    case(0):
      return m_treeview_parts_header;
    case(1):
      return m_treeview_parts_main;
    case(2):
      return m_treeview_parts_footer;
    default:
    {
      std::cerr << "Dialog_Layout_Report::get_selected_treeview(): Unrecognised current notebook page:"  << m_notebook_parts->get_current_page() << std::endl;
      return 0;
    }
  }
}
