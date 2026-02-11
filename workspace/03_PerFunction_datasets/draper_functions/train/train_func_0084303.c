WriteInternal()
{
  if (!this->OpenFile())
    {
    return 0;
    }

  (*this->Stream).imbue(std::locale::classic());


  int result = this->WriteData();


  if( this->UserContinueExecuting != 1 )
    {
    this->CloseFile();
    }

  return result;
}
