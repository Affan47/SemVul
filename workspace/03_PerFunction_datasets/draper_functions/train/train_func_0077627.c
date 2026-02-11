get_discriminator()
{
  CHECK_NOT_DESTROYED;
  pd_disc->_NP_incrRefCount();
  return pd_disc;
}
