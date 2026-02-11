empty(network_address_type_t type)
{
  Lock lock(mutex_);
  return routes_[type].empty();
}
