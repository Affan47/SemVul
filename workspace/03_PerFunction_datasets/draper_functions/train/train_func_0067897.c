alloc_dwarf1_unit (struct dwarf1_debug* stash)
{
  bfd_size_type amt = sizeof (struct dwarf1_unit);

  struct dwarf1_unit* x = (struct dwarf1_unit *) bfd_zalloc (stash->abfd, amt);
  if (x)
    {
      x->prev = stash->lastUnit;
      stash->lastUnit = x;
    }

  return x;
}
