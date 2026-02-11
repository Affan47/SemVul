set (const ACE_SPIPE_Addr &sa)
{
  this->base_set (sa.get_type (), sa.get_size ());

  if (sa.get_type () == AF_ANY)
    (void) ACE_OS::memset ((void *) &this->SPIPE_addr_,
                           0,
                           sizeof this->SPIPE_addr_);
  else
    (void) ACE_OS::memcpy ((void *) &this->SPIPE_addr_, (void *)
                           &sa.SPIPE_addr_,
                           sa.get_size ());
  return 0;
}
