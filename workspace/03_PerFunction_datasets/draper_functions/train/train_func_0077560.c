taxisDestroy(int taxisID)
{
  taxis_t *taxisptr;

  taxisptr = ( taxis_t * ) reshGetVal ( taxisID, &taxisOps );

  if ( taxisptr->name     ) free(taxisptr->name);
  if ( taxisptr->longname ) free(taxisptr->longname);

  taxisDestroyKernel ( taxisptr );
}
