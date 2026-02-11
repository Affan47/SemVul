FreeSearchStructure(void)
{
  if (this->mRoot)
    {
    delete this->mRoot;
    }
  this->mRoot                     = NULL;
  this->Level        = 0;
  this->npn = this->nln = this->tot_depth = 0;
}
