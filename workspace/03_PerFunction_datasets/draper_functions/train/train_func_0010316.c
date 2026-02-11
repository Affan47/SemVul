GetBounds(double *bounds)
{
  REGIONCHECK(1);

  this->Cuts->GetKdNodeTree()->GetBounds(bounds);

  return 0;
}
