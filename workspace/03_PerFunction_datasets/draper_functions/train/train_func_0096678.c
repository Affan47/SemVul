DateTimeSingleValueMatch( const char *datasetDateValue, const char *datasetTimeValue, const char *searchMaskDateValue, const char *searchMaskTimeValue )


{
  OFDate datasetDateVal, searchMaskDateVal;
  OFTime datasetTimeVal, searchMaskTimeVal;
  OFCondition cond;


  if( strcmp( searchMaskDateValue, "" ) == 0 && strcmp( searchMaskTimeValue, "" ) == 0 )
  {
    return( OFTrue );
  }
  else
  {

    OFBool dateValuesMatch = OFFalse;
    OFBool timeValuesMatch = OFFalse;


    if( strcmp( searchMaskDateValue, "" ) == 0 )
    {

      dateValuesMatch = OFTrue;
    }
    else
    {

      if( datasetDateValue == NULL )
      {

        dateValuesMatch = OFFalse;
      }
      else
      {


        char *ddv = new char[ strlen( datasetDateValue ) + 1 ];     strcpy( ddv, datasetDateValue );
        char *sdv = new char[ strlen( searchMaskDateValue ) + 1 ];  strcpy( sdv, searchMaskDateValue );


        ddv = DU_stripTrailingSpaces( ddv );
        sdv = DU_stripTrailingSpaces( sdv );


        cond = DcmDate::getOFDateFromString( OFString( ddv ), datasetDateVal );
        if( cond.good() )
        {
          cond = DcmDate::getOFDateFromString( OFString( sdv ), searchMaskDateVal );
          if( cond.good() )
          {


            if( searchMaskDateVal == datasetDateVal )
            {

              dateValuesMatch = OFTrue;
            }
          }
        }


        delete ddv;
        delete sdv;
      }
    }


    if( strcmp( searchMaskTimeValue, "" ) == 0 )
    {

      timeValuesMatch = OFTrue;
    }
    else
    {

      if( datasetTimeValue == NULL )
      {

        timeValuesMatch = OFFalse;
      }
      else
      {


        char *dtv = new char[ strlen( datasetTimeValue ) + 1 ];     strcpy( dtv, datasetTimeValue );
        char *stv = new char[ strlen( searchMaskTimeValue ) + 1 ];  strcpy( stv, searchMaskTimeValue );


        dtv = DU_stripTrailingSpaces( dtv );
        stv = DU_stripTrailingSpaces( stv );


        cond = DcmTime::getOFTimeFromString( OFString( dtv ), datasetTimeVal );
        if( cond.good() )
        {
          cond = DcmTime::getOFTimeFromString( OFString( stv ), searchMaskTimeVal );
          if( cond.good() )
          {


            if( searchMaskTimeVal == datasetTimeVal )
            {

              timeValuesMatch = OFTrue;
            }
          }
        }


        delete dtv;
        delete stv;
      }
    }


    if( dateValuesMatch && timeValuesMatch )
      return( OFTrue );
    else
      return( OFFalse );
  }
}
