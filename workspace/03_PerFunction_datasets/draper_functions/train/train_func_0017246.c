operator==(const LayoutItem_Line& src) const
{
  bool result = LayoutItem::operator==(src) &&
                (m_start_x == src.m_start_x) &&
                (m_start_y == src.m_start_y) &&
                (m_end_x == src.m_end_x) &&
                (m_end_y == src.m_end_y) &&
                (m_line_width == src.m_line_width) &&
                (m_color == src.m_color);

  return result;
}
