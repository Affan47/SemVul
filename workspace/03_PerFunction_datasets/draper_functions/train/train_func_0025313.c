total_capacity (void) const
{
  ACE_TRACE ("ACE_Message_Block::total_capacity");

  size_t size = 0;

  for (const ACE_Message_Block *i = this;
       i != 0;
       i = i->cont ())
    size += i->capacity ();

  return size;
}
