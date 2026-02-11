FillFromDataPointer(int nb, double *ptr)
{
  if (nb <= 0 || !ptr)
    {
    return;
    }

  this->RemoveAllPoints();

  while (nb)
    {
    this->AddRGBPoint(ptr[0], ptr[1], ptr[2], ptr[3]);
    ptr += 4;
    nb--;
    }
}
