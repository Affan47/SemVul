inputwarning(nwarning, par1, par2)
long nwarning, par1, par2;
{
  printf("Warning number from procedure inputdata\n");
  switch (nwarning) {

  case 0:
    printf("Illegal sex difference parameter %2ld Parameter should be 0, 1, or 2\n",
	   par1);
    break;

  case 1:
    printf("Illegal interference parameter %2ld Lack of interference assumed\n",
	   par1);
    break;

  case 2:
    printf(
      "Illegal sex difference parameter %2ld Parameter must be 0 with sex-linked data\n",
      par1);
    break;

  case 3:
    printf(
      "Non-standard affection status%4ld interpreted as normal in pedigree record%5ld\n",
      par2, par1);
    break;
  }
  respond();
}
