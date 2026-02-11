zero_momentum()
{
  for (int ibody = 0; ibody < nbody; ibody++)
    vcm[ibody][0] = vcm[ibody][1] = vcm[ibody][2] = 0.0;

  evflag = 0;
  set_v();
}
