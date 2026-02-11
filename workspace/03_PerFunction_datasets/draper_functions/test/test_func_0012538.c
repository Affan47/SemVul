total_size_and_length (size_t &mb_size,
                                          size_t &mb_length) const
{
  ACE_TRACE ("ACE_Message_Block::total_size_and_length");

  for (const ACE_Message_Block *i = this;
       i != 0;
       i = i->cont ())
    {
      mb_size += i->size ();
      mb_length += i->length ();
    }
}
