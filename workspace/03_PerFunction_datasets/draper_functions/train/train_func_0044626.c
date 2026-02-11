fdd_flip( fdd_t *d, int upsidedown )
{
  if( !d->loaded )
    return;

  d->upsidedown = upsidedown > 0 ? 1 : 0;
  fdd_set_data( d, FDD_LOAD_FACT );
}
