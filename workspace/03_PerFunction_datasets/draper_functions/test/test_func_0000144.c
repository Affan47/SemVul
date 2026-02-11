count_nb_dec (int dec)
{
  int size = 1;

  while (dec /= 10)
    size++;

  return size;
}
