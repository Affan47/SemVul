fdd_select( fdd_t *d, int select )
{
  d->selected = select > 0 ? 1 : 0;


  if( d->type == FDD_SHUGART )
    fdd_head_load( d, d->selected );
}
