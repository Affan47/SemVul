GetValue(vtkIdType id)
{
  if (this->Array[id/8]&(0x80 >> (id%8)))
    {
    return 1;
    }
  return 0;
}
