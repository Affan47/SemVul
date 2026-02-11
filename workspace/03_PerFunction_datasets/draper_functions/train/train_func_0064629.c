GetElementFaces(int elemtype)
{
  int basetype=0,elemfaces=0;

  basetype = elemtype / 100;

  switch (basetype) {
  case 1:
    elemfaces = 0;
    break;
  case 2:
    elemfaces = 2;
    break;
  case 3:
    elemfaces = 3;
    break;
  case 4:
    elemfaces = 4;
    break;
  case 5:
    elemfaces = 4;
    break;
  case 6:
    elemfaces = 5;
    break;
  case 7:
    elemfaces = 5;
    break;
  case 8:
    elemfaces = 6;
    break;

  default:
    printf("GetElementFaces: Unknown elementtype %d\n",elemfaces);
  }

  return(elemfaces);
}
