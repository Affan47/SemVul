avail()
{
  if (status_.good()) return outputBufCount_; else return 0;
}
