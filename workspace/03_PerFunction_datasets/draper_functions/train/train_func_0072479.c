udi_compress_tracks( disk_t *d )
{
  int i, tlen;
  libspectrum_byte *data = NULL;
  size_t clen, data_size = 0;

  for( i = 0; i < d->sides * d->cylinders; i++ ) {
    DISK_SET_TRACK_IDX( d, i );
    if( d->track[-1] == 0xf0 ) continue;

    tlen = UDI_TLEN( d->track[-1], d->track[-3] + 256 * d->track[-2] );

    if( udi_write_compressed( d->track, tlen, &clen, &data, &data_size ) ||
							clen < 1 ) continue;

    if( clen > 65535 || clen >= tlen ) continue;
    d->track[0] = d->track[-1];
    d->track[1] = d->track[-3];
    d->track[2] = d->track[-2];
    memcpy( d->track + 3, data, clen );
    clen--;
    d->track[-1] = 0xf0;
    d->track[-3] = clen & 0xff;
    d->track[-2] = ( clen >> 8 ) & 0xff;
  }
  if( data ) libspectrum_free( data );
  return DISK_OK;
}
