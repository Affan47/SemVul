modulate(int i)
{
  d->lngSeed2 -= i;
  if ( d->lngSeed2 < 0 )
  {
    d->lngShufflePos += sMod2;
  }
  d->draw();
  d->lngSeed1 -= i;
  if ( d->lngSeed1 < 0 )
  {
    d->lngSeed1 += sMod1;
  }
  d->draw();
}
