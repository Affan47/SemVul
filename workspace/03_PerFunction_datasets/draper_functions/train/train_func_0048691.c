startGrid(const GridNIC &nic)
{
  os() << "<grid";
  if (nic.nColumns)
    os() << " grid-n-columns=" << quot << (unsigned long)nic.nColumns << quot;
  if (nic.nRows)
    os() << " grid-n-rows=" << quot << (unsigned long)nic.nRows << quot;
  outputIcs();
  os() << '>' << RE;
}
