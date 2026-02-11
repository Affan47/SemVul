nthComponentTC(unsigned n)
{
  if( n >= pd_n_components )
    throw omniORB::fatalException(__FILE__,__LINE__,
		    "DynStructImpl::nthComponentTC() - n out of bounds");

  return actualTc()->NP_member_type(n);
}
