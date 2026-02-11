ef(unsigned n)
{
  switch (n%3) {
  case 0:
  case 2:
    return 1;
  case 1:
    return 2*(n/3);
  }
}
