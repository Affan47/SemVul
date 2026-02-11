GetElementDimension(int elementtype)
{
  int elemdim;

  switch (elementtype / 100) {
  case 1:
    elemdim = 0;
    break;
  case 2:
    elemdim = 1;
    break;
  case 3:
  case 4:
    elemdim = 2;
    break;
  case 5:
  case 6:
  case 7:
  case 8:
    elemdim = 3;
    break;
  default:
    printf("GetElementDimension: unknown elementtype %d\n",elementtype);

  }
  return(elemdim);
}
