GetMTime()
{
  unsigned long mt = this->MTime;
  unsigned long tmp;

  if ( this->Tessellator )
    {
    tmp = this->Tessellator->GetMTime();
    if ( tmp > mt )
      mt = tmp;
    }

  if ( this->Subdivider )
    {
    tmp = this->Subdivider->GetMTime();
    if ( tmp > mt )
      mt = tmp;
    }

  return mt;
}
