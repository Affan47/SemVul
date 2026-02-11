reset (void)
{
  while (this->popContext() != -1)
    ;
  return 0;
}
