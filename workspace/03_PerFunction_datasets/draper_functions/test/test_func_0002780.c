EndPage(void)
{


  if (NumPlanes > 1)
  {
     printf("\033*rC");

     if (!(Duplex && (Page & 1)))
       printf("\033&l0H");
  }
  else
  {
     printf("\033*r0B");

     if (!(Duplex && (Page & 1)))
       printf("\014");
  }

  fflush(stdout);


  free(Planes[0]);

  if (BitBuffer)
    free(BitBuffer);

  if (CompBuffer)
    free(CompBuffer);
}
