ComputeDataElement(const PrivateTag & t) const
{
  gdcmDebugMacro( "Entering ComputeDataElement" );


  const Tag start(t.GetGroup(), 0x0010 );
  const DataElement r(start);
  ConstIterator it = DES.lower_bound(r);
  const char *refowner = t.GetOwner();
  assert( refowner );
  bool found = false;
  while( it != DES.end() && it->GetTag().GetGroup() == t.GetGroup() && it->GetTag().GetElement() < 0x100 )
    {

    const ByteValue * bv = it->GetByteValue();
    assert( bv );


    std::string tmp(bv->GetPointer(),bv->GetLength());

    tmp.erase(tmp.find_last_not_of(' ') + 1);
    assert( tmp.size() == 0 || tmp[ tmp.size() - 1 ] != ' ' );
    if( System::StrCaseCmp( tmp.c_str(), refowner ) == 0 )
      {

      found = true;
      break;
      }
    ++it;
    }
  gdcmDebugMacro( "In compute found is:" << found );
  if (!found) return GetDEEnd().GetTag();


  Tag copy = t;
  copy.SetPrivateCreator( it->GetTag() );
  gdcmDebugMacro( "Compute found:" << copy );
  return copy;
}
