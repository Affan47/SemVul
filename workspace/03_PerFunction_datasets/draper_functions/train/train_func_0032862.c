GetBounds(double bounds[6])
{
  this->GetBounds();
  for (int i=0; i < 6; i++)
    {
    bounds[i] = this->Bounds[i];
    }
}
