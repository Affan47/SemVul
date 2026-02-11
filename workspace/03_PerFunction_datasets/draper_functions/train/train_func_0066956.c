remove(CORBA::ULong index)
{
  if (index >= pd_list.length())
    throw CORBA::NVList::Bounds();


  CORBA::release(pd_list[index]);

  for( CORBA::ULong i = index; i < pd_list.length() - 1; i++ )
    pd_list[i] = pd_list[i + 1];

  pd_list.length(pd_list.length() - 1);
}
