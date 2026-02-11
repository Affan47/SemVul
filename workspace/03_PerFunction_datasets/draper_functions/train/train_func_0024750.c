varDefZaxis(int vlistID, int zaxistype, int nlevels, double *levels, int lbounds,
		double *levels1, double *levels2, int vctsize, double *vct, char *name,
		char *longname, char *units, int prec, int mode, int ltype)
{


  int zaxisdefined;
  int nzaxis;
  int zaxisID = UNDEFID;
  int index;
  int zaxisglobdefined = 0;
  vlist_t *vlistptr;
  int i;

  vlistptr = vlist_to_pointer(vlistID);

  zaxisdefined = 0;
  nzaxis = vlistptr->nzaxis;

  if ( mode == 0 )
    for ( index = 0; index < nzaxis; index++ )
      {
	zaxisID = vlistptr->zaxisIDs[index];

	if ( zaxisCompare(zaxisID, zaxistype, nlevels, lbounds, levels, longname, units, ltype) == 0 )
	  {
	    zaxisdefined = 1;
	    break;
	  }
      }

  if ( ! zaxisdefined )
    {
      nzaxis = zaxisSize();
      if ( nzaxis > 0 )
        {
          int *zaxisIndexList;
          zaxisIndexList = (int *) malloc ( nzaxis * sizeof ( int ));
          zaxisGetIndexList ( nzaxis, zaxisIndexList );
          for ( i = 0; i < nzaxis; i++ )
            {
              zaxisID = zaxisIndexList[i];
              if ( zaxisCompare(zaxisID, zaxistype, nlevels, lbounds, levels, longname, units, ltype) == 0 )
                {
                  zaxisglobdefined = 1;
                  break;
                }
            }
          if ( zaxisIndexList ) free ( zaxisIndexList );
        }

      nzaxis = vlistptr->nzaxis;
      if ( mode == 1 )
	for ( index = 0; index < nzaxis; index++ )
	  if ( vlistptr->zaxisIDs[index] == zaxisID )
	    {
	      zaxisglobdefined = FALSE;
	      break;
	    }
    }

  if ( ! zaxisdefined )
    {
      if ( ! zaxisglobdefined )
	{
	  zaxisID = zaxisCreate(zaxistype, nlevels);
	  zaxisDefLevels(zaxisID, levels);
	  if ( lbounds )
	    {
	      zaxisDefLbounds(zaxisID, levels1);
	      zaxisDefUbounds(zaxisID, levels2);
	    }

	  if ( zaxistype == ZAXIS_HYBRID || zaxistype == ZAXIS_HYBRID_HALF )
	    {


	      if ( vctsize > 0 )
		zaxisDefVct(zaxisID, vctsize, vct);
	      else
		Warning("VCT missing");
	    }

	  zaxisDefName(zaxisID, name);
	  zaxisDefLongname(zaxisID, longname);
	  zaxisDefUnits(zaxisID, units);
	  zaxisDefPrec(zaxisID, prec);
	  zaxisDefLtype(zaxisID, ltype);
	}

      nzaxis = vlistptr->nzaxis;
      vlistptr->zaxisIDs[nzaxis] = zaxisID;
      vlistptr->nzaxis++;
    }

  return (zaxisID);
}
