gridInqRowlon(int gridID, int *rowlon)
{
  grid_t *gridptr;

  gridptr = ( grid_t *) reshGetVal ( gridID, &gridOps );

  grid_check_ptr(gridID, gridptr);

  if ( gridptr->rowlon == 0 )  Error("undefined pointer!");

  memcpy(rowlon, gridptr->rowlon, gridptr->nrowlon*sizeof(int));
}
