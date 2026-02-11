component_to_any(unsigned i, CORBA::Any& a)
{
  a.replace(nthComponentTC(i), 0);

  if( i < pd_n_in_buf ) {
    if( pd_read_index != (int)i )  seekTo(i);
    try {
      CORBA::TypeCode_var tc = a.type();
      tcParser::copyStreamToStream(tc, pd_buf,
				   a.PR_streamToWrite());
    }
    catch(CORBA::MARSHAL&) {
      throw omniORB::fatalException(__FILE__,__LINE__,
	 "DynAnyConstrBase::component_to_any() - unexpected exception");
    }
    pd_read_index++;
    return 1;
  }
  else if( i >= pd_first_in_comp ) {
    cdrAnyMemoryStream& buf = a.PR_streamToWrite();
    return pd_components[i]->copy_to(buf);
  }
  else
    return 0;
}
