set (const ACE_UNIX_Addr &sa)
{
  if (sa.get_type () == AF_ANY)
    (void) ACE_OS::memset ((void *) &this->unix_addr_,
                           0,
                           sizeof this->unix_addr_);
  else
    ACE_OS::strcpy (this->unix_addr_.sun_path,
                    sa.unix_addr_.sun_path);

  this->unix_addr_.sun_family = AF_UNIX;
  this->base_set (sa.get_type (), sa.get_size ());

  return 0;
}
