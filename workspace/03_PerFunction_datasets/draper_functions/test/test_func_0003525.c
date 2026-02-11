getView(void) const
{
  fp_Page * pPage = getPage();
  if(pPage == NULL)
  {
    return NULL;
  }
  FL_DocLayout * pDL = pPage->getDocLayout();
  if(pDL == NULL)
  {
    return NULL;
  }
  return pDL->getView();
}
