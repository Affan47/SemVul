insertCell(const unsigned column, const unsigned row, const KEYObjectPtr_t &content, const unsigned columnSpan, const unsigned rowSpan)
{
  if ((m_rowSizes.size() <= row) || (m_columnSizes.size() <= column))
    return;

  Cell cell;
  cell.content = content;
  cell.columnSpan = columnSpan;
  cell.rowSpan = rowSpan;
  m_table[row][column] = cell;
}
