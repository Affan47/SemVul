CheckMatchingKey( const DcmElement *elem )


{
  OFBool ok = OFTrue;
  OFString val;

  switch( elem->ident() )
  {
    case EVR_DA:

      ok = GetStringValue( elem, val );

      if( ok && !IsValidDateOrDateRange( val ) )
      {
        DcmTag tag( elem->getTag() );
        PutOffendingElements( tag );
        errorComment->putString("Invalid value for an attribute of datatype DA");
        ok = OFFalse;
      }
      else
        return OFTrue;

    case EVR_TM:

      ok = GetStringValue( elem, val );

      if( ok && !IsValidTimeOrTimeRange( val ) )
      {
        DcmTag tag( elem->getTag() );
        PutOffendingElements( tag );
        errorComment->putString("Invalid value for an attribute of datatype TM");
        ok = OFFalse;
      }
      else
        return OFTrue;

    case EVR_CS:

      ok = GetStringValue( elem, val );

      if( ok && !ContainsOnlyValidCharacters( val.c_str(), "*?ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 _" ) )
      {
        DcmTag tag( elem->getTag() );
        PutOffendingElements( tag );
        errorComment->putString("Invalid Character Repertoire for datatype CS");
        ok = OFFalse;
      }
      else
        return OFTrue;

    case EVR_AE:

      ok = GetStringValue( elem, val );

      if( ok && !ContainsOnlyValidCharacters( val.c_str(), " !\"#$%%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" ) )
      {
        DcmTag tag( elem->getTag() );
        PutOffendingElements( tag );
        errorComment->putString("Invalid Character Repertoire for datatype AE");
        ok = OFFalse;
      }
      else
        return OFTrue;

    case EVR_PN:

      ok = GetStringValue( elem, val );

      if( ok && !ContainsOnlyValidCharacters( val.c_str(), "*? !\"#$%%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\033" ) && specificCharacterSet == "" )
      {
        DcmTag tag( elem->getTag() );
        PutOffendingElements( tag );
        errorComment->putString("Invalid Character Repertoire for datatype PN");
        ok = OFFalse;
      }
      else
        return OFTrue;

    case EVR_LO:

      ok = GetStringValue( elem, val );

      if( ok && !ContainsOnlyValidCharacters( val.c_str(), "*? !\"#$%%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\033\012\014\015" ) && specificCharacterSet == "" )
      {
        DcmTag tag( elem->getTag() );
        PutOffendingElements( tag );
        errorComment->putString("Invalid Character Repertoire for datatype LO");
        ok = OFFalse;
      }
      else
        return OFTrue;

    case EVR_SH:

      ok = GetStringValue( elem, val );

      if( ok && !ContainsOnlyValidCharacters( val.c_str(), "*? !\"#$%%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\033\012\014\015" ) && specificCharacterSet == "" )
      {
        DcmTag tag( elem->getTag() );
        PutOffendingElements( tag );
        errorComment->putString("Invalid Character Repertoire for datatype SH");
        ok = OFFalse;
      }
      else
        return OFTrue;

    default:
      break;
  }

  return( ok );
}
