GetPickedIds(unsigned int atMost,
                                    unsigned int *callerBuffer)
{
  if (!this->PickInfo->PickBuffer)
    {
    return 0;
    }

  unsigned int max = (atMost < this->PickInfo->NumPicked) ? atMost : this->PickInfo->NumPicked;
  GLuint* iptr = this->PickInfo->PickBuffer;
  unsigned int *optr = callerBuffer;
  unsigned int k;
  for(k =0; k < max; k++)
    {
    int num_names = *iptr;
    iptr++;
    iptr++;
    iptr++;
    *optr = static_cast<unsigned int>(*iptr);
    optr++;

    iptr += num_names;
    }
  return k;
}
