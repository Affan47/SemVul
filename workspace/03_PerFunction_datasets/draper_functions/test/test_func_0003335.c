lines()
{
  Q3CanvasItemList list;

  SegmentLine* line;
  for (line = m_lines.first(); line; line = m_lines.next())
    list.append((Q3CanvasLine*) line);

  return list;
}
