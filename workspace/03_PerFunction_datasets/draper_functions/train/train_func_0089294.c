property_table_matches (const void *ap, const void *bp)
{
  const property_table_entry *a = (const property_table_entry *) ap;
  const property_table_entry *b = (const property_table_entry *) bp;


  if ((b->address >= a->address && b->address < (a->address + a->size))
      || (a->address >= b->address && a->address < (b->address + b->size)))
    return 0;

  return (a->address - b->address);
}
