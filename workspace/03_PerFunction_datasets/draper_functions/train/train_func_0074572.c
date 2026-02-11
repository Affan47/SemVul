collectPresentation(const boost::optional<KEYSize> &size)
{
  optional<KEYSize> size_(size);
  getDefaults().applyPresentationSize(size_);
  assert(size_);
  m_size = get(size_);
}
