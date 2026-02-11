dunitize (double r [3], double ur [3])


{
  double rmag;
  int i;

    rmag = dvmag1 (r);
    for (i = 0; i < 3; i++)
    ur [i] = r [i] / rmag;
}
