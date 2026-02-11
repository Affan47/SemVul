newDpoint(int number)
{
  const char   modName[] = "newDpoint";
  int          i;
  VimosDpoint *tPoint;

  if (number <= 0) {
    cpl_msg_error(modName, "Invalid argument");
    return(NULL);
  }


  tPoint = (VimosDpoint *) pil_calloc(number, sizeof(VimosDpoint));


  if (tPoint == NULL) {
    cpl_msg_error(modName, "Allocation error");
    return(NULL);
  }


  switch (number) {
  case 1:
    {
      tPoint->prev = tPoint->next = NULL;
      break;
    }
  default:
    {
      for (i = 1; i < number-1; i++) {
        tPoint[i].next = &(tPoint[i+1]);
        tPoint[i].prev = &(tPoint[i-1]);
      }
      tPoint[0].prev = NULL;
      tPoint[0].next = &(tPoint[1]);
      tPoint[number-1].prev = &(tPoint[number-2]);
      tPoint[number-1].next = NULL;
      break;
    }
  }

  return(tPoint);
}
