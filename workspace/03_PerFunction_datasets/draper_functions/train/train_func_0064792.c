__mpatan2 (mp_no *y, mp_no *x, mp_no *z, int p)
{
  mp_no mpt1, mpt2, mpt3;

  if (X[0] <= 0)
    {
      __dvd (x, y, &mpt1, p);
      __mul (&mpt1, &mpt1, &mpt2, p);
      if (mpt1.d[0] != 0)
	mpt1.d[0] = 1;
      __add (&mpt2, &mpone, &mpt3, p);
      __mpsqrt (&mpt3, &mpt2, p);
      __add (&mpt1, &mpt2, &mpt3, p);
      mpt3.d[0] = Y[0];
      __mpatan (&mpt3, &mpt1, p);
      __add (&mpt1, &mpt1, z, p);
    }
  else
    {
      __dvd (y, x, &mpt1, p);
      __mpatan (&mpt1, z, p);
    }
}
