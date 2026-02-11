rowCount(unsigned index_)
{
  return index_<columnRowCounts().length()?columnRowCounts()(index_):fixedRowCount();
}
