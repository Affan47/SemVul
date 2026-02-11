BuildLinesFromHandles()
{
  this->ResetLine(this->HandleGeometry[0]->GetCenter());

  for ( int i = 1; i < this->NumberOfHandles; ++i )
    {
    this->AppendLine(this->HandleGeometry[i]->GetCenter());
    }
}
