zaxisDefLevel(int zaxisID, int levelID, double level)
{
  zaxis_t *zaxisptr;

  if ( reshGetStatus ( zaxisID, &zaxisOps ) == CLOSED )
    {
      xwarning("%s", "Operation not executed.");
      return;
    }

  zaxisptr = ( zaxis_t * ) reshGetVal ( zaxisID, &zaxisOps );

  zaxis_check_ptr(zaxisID, zaxisptr);

  if ( levelID >= 0 && levelID < zaxisptr->size )
    zaxisptr->vals[levelID] = level;
}
