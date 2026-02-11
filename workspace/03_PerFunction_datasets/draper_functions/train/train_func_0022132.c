FreeAllElements()
{
  while(this->NumberOfOpenElements > 0)
    {
    --this->NumberOfOpenElements;
    this->OpenElements[this->NumberOfOpenElements]->Delete();
    this->OpenElements[this->NumberOfOpenElements] = 0;
    }
  if(this->RootElement)
    {
    this->RootElement->Delete();
    this->RootElement = 0;
    }
}
