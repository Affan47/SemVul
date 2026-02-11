get_line() const
{
  if(!m_line)
  {
    std::cerr << G_STRFUNC <<  ": m_line is null" << std::endl;
  }

  sharedptr<LayoutItem_Line> result = glom_sharedptr_clone(m_line);

  if(!result)
  {
    std::cerr << ": result is null" << std::endl;
    return result;
  }

  result->set_line_width( m_spinbutton_line_width->get_value() );
  result->set_line_color( m_colorbutton->get_rgba().to_string() );

  return result;
}
