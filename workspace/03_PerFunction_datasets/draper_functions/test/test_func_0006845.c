substract_times (struct timeval a, struct timeval b)
{
  struct timeval result;


  if (a.tv_usec < b.tv_usec)
    {
      int nsec = (b.tv_usec - a.tv_usec) / 1000000 + 1;
      b.tv_usec -= 1000000 * nsec;
      b.tv_sec += nsec;
    }
  if (a.tv_usec - b.tv_usec > 1000000)
    {
      int nsec = (a.tv_usec - b.tv_usec) / 1000000;
      b.tv_usec += 1000000 * nsec;
      b.tv_sec -= nsec;
    }


  result.tv_sec = a.tv_sec - b.tv_sec;
  result.tv_usec = a.tv_usec - b.tv_usec;
  return result;
}
