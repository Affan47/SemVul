IsValidDateOrDateRange( const OFString& value )


{

  OFString dateRange = DeleteLeadingAndTrailingBlanks( value );

  if (dateRange.length() == 0)
    return OFFalse;


  if( !ContainsOnlyValidCharacters( dateRange.c_str(), "0123456789.-" ) )
    return( OFFalse );


  OFBool isValidDateRange = OFFalse;


  size_t hyphen = dateRange.find('-');
  if( hyphen != OFString_npos )
  {

    if( dateRange[0] == '-' )
    {

      isValidDateRange = IsValidDate( dateRange.substr(1) );
    }
    else if( dateRange[ dateRange.length() - 1 ] == '-' )
    {

      isValidDateRange = IsValidDate( dateRange.substr(0, dateRange.length() -1 ));
    }
    else
    {


      if( IsValidDate( dateRange.substr(0, dateRange.length()-hyphen-1 )) &&
          IsValidDate( dateRange.substr(        hyphen + 1             )) )
      {
        isValidDateRange = OFTrue;
      }
    }
  }
  else
  {

    isValidDateRange = IsValidDate( dateRange );
  }


  return( isValidDateRange );
}
