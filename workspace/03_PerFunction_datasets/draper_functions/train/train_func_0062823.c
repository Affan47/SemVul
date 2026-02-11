write_trd( FILE *file, disk_t *d )
{
  int i, j, sbase, sectors, seclen, mfm, cyl;

  if( check_disk_geom( d, &sbase, &sectors, &seclen, &mfm, &cyl ) ||
      sbase != 1 || seclen != 1 || sectors != 16 )
    return d->status = DISK_GEOM;

  if( cyl == -1 ) cyl = d->cylinders;
  for( i = 0; i < cyl; i++ ) {
    for( j = 0; j < d->sides; j++ ) {
      if( savetrack( d, file, j, i, 1, sectors, seclen ) )
	return d->status = DISK_GEOM;
    }
  }
  return d->status = DISK_OK;
}
