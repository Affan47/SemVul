write_data(FILE *fp)
{
  for (int i = 1; i <= atom->nbondtypes; i++)
    fprintf(fp,"%d %g %g %g %g\n",i,r0[i],k2[i],k3[i],k4[i]);
}
