Clear()
{
  BitSample = 0;
  IncompleteLUT = false;
  delete Internal;
  Internal = new LookupTableInternal;
}
