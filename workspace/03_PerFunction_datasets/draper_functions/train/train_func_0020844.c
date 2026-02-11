set (const ACE_DEV_Addr &sa)
{
  this->base_set (sa.get_type (), sa.get_size ());

  if (sa.get_type () == AF_ANY)
    (void) ACE_OS::memset ((void *) &this->devname_,
                           0,
                           sizeof this->devname_);
  else
    (void) ACE_OS::strsncpy (this->devname_,
                             sa.devname_,
                             ACE_DEV_Addr::DEVNAME_LENGTH);
  return 0;
}
