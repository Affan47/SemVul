setprop(int obj, int prop, long val)
{
  integer *paddr;

  if (prop>=NUM_WPROP) {
    writeln("GAME ERROR: Read-only or non-existant property.");
    return;
  }

  paddr=(integer*)compute_addr(obj,prop,proplist);
  if (paddr==NULL) {
    writeln("GAME ERROR: Property-object mismatch.");
    return;
  }
  *paddr=val;
}
