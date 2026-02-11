RunTests()
{
  this->CheckResume();
  if(!this->CheckCycles())
    {
    return;
    }
  this->TestHandler->SetMaxIndex(this->FindMaxIndex());
  this->StartNextTests();
  while(this->Tests.size() != 0)
    {
    if(this->StopTimePassed)
      {
      return;
      }
    this->CheckOutput();
    this->StartNextTests();
    }

  while(this->CheckOutput())
    {
    }
  this->MarkFinished();
  this->UpdateCostData();
}
