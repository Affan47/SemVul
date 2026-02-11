operator= (const HTMLElementList& list)
{
  fElements = list.fElements;

  std::vector<HTMLElement*>::iterator iter;
  for(iter = fElements.begin(); iter != fElements.end(); ++iter)
    *iter = (*iter)->clone();

  return *this;
}
