DeleteQueue()
{
  if (this->Queue)
    {
    this->Queue->Delete();
    }
  this->Queue=NULL;
}
