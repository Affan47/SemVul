copy_to(cdrAnyMemoryStream& mbs)
{
  if( !pd_disc->copy_to(mbs) )  return 0;

  return !pd_member || pd_member->copy_to(mbs);
}
