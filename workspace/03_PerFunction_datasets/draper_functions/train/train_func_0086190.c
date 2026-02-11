clear()
{
  if (array)
  {
  	for (unsigned long i=0; i < numColors; i++) delete array[i];
    delete[] array;
    array = NULL;
  }
  numColors = 0;
  maxval = 0;
}
