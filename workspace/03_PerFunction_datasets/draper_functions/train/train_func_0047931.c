Split()
{
  Output = Input;
  const Pixmap &image = *Input;

  const unsigned int *dims = image.GetDimensions();
  if( dims[2] != 1 )
    {
    gdcmDebugMacro( "Cannot split a 3D image" );
    return false;
    }
  const DataElement& pixeldata = image.GetDataElement();

  const SequenceOfFragments *sqf = pixeldata.GetSequenceOfFragments();
  if( !sqf )
    {
    gdcmDebugMacro( "Cannot split a non-encapsulated syntax" );
    return false;
    }

  if ( sqf->GetNumberOfFragments() != 1 )
    {
    gdcmDebugMacro( "Case not handled (for now)" );
    return false;
    }


  const Fragment& frag = sqf->GetFragment(0);
  const ByteValue *bv = frag.GetByteValue();
  const char *p = bv->GetPointer();
  size_t len = bv->GetLength();
  if( FragmentSizeMax > len && !Force )
    {

    return true;
    }

  if( FragmentSizeMax == 0 )
    {
    gdcmDebugMacro( "Need to set a real value for fragment size" );
    return false;
    }
  size_t nfrags = len / FragmentSizeMax;
  size_t lastfrag = len % FragmentSizeMax;

  SmartPointer<SequenceOfFragments> sq = new SequenceOfFragments;

  for(size_t i = 0; i < nfrags; ++i)
    {
    Fragment splitfrag;
    splitfrag.SetByteValue( p + i * FragmentSizeMax, FragmentSizeMax);
    sq->AddFragment( splitfrag );
    }

  if( lastfrag )
    {
    Fragment splitfrag;
    splitfrag.SetByteValue( p + nfrags * FragmentSizeMax, (uint32_t)lastfrag );
    assert( nfrags * FragmentSizeMax + lastfrag == len );
    sq->AddFragment( splitfrag );
    }
  Output->GetDataElement().SetValue( *sq );

  bool success = true;
  return success;
}
