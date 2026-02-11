zaxisDefine(zaxis_t zaxis)
{
  int zaxisID = UNDEFID;

  if ( zaxis.type == -1 ) Error("zaxistype undefined!");

  if ( zaxis.size == 0 ) Error("zaxis size undefined!");

  zaxisID = zaxisCreate(zaxis.type, zaxis.size);

  if ( zaxis.vals )
    {
      zaxisDefLevels(zaxisID, zaxis.vals);
      free(zaxis.vals);
    }
  if ( zaxis.lbounds )
    {
      zaxisDefLbounds(zaxisID, zaxis.lbounds);
      free(zaxis.lbounds);
    }
  if ( zaxis.ubounds )
    {
      zaxisDefUbounds(zaxisID, zaxis.ubounds);
      free(zaxis.ubounds);
    }

  if ( zaxis.name[0] )     zaxisDefName(zaxisID, zaxis.name);
  if ( zaxis.longname[0] ) zaxisDefLongname(zaxisID, zaxis.longname);
  if ( zaxis.units[0] )    zaxisDefUnits(zaxisID, zaxis.units);

  if ( zaxis.type == ZAXIS_HYBRID || zaxis.type == ZAXIS_HYBRID_HALF )
    {
      if ( zaxis.vctsize && zaxis.vct )
	zaxisDefVct(zaxisID, zaxis.vctsize, zaxis.vct);
      else
	Warning("vct undefined!");
    }

  return (zaxisID);
}
