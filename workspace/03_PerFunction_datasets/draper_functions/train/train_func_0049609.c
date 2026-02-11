vg_freeDestroy( VolumeGeometry **p_obj )
{
  VolumeGeometry *obj = *p_obj;

  if (!obj) return( RET_OK );

  if (obj->bfGM)
    fmf_freeDestroy( &(obj->bfGM) );
  if (obj->det)
    fmf_freeDestroy( &(obj->det) );
  if (obj->volume)
    fmf_freeDestroy( &(obj->volume) );
  free_mem( *p_obj );

  return( RET_OK );
}
