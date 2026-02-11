cleanFactorization(int ifValuesPass)
{
  int status = internalFactorize(ifValuesPass ? 10 : 0);
  if (status < 0) {
    return 1;
  } else {
    firstFree_=0;
    return 0;
  }
}
