Load_ClassDef2( HB_ClassDefinition*  cd,
				 HB_UShort             limit,
				 HB_Stream             stream )
{
  HB_Error   error;

  HB_UShort              n, count;

  HB_ClassRangeRecord*  crr;

  HB_ClassDefFormat2*   cdf2;


  cdf2 = &cd->cd.cd2;

  if ( ACCESS_Frame( 2L ) )
    return error;

  count = GET_UShort();
  cdf2->ClassRangeCount = 0;

  FORGET_Frame();

  cdf2->ClassRangeRecord = NULL;

  if ( ALLOC_ARRAY( cdf2->ClassRangeRecord, count, HB_ClassRangeRecord ) )
    return error;

  crr = cdf2->ClassRangeRecord;

  if ( ACCESS_Frame( count * 6L ) )
    goto Fail;

  for ( n = 0; n < count; n++ )
  {
    crr[n].Start = GET_UShort();
    crr[n].End   = GET_UShort();
    crr[n].Class = GET_UShort();


    if ( crr[n].Start > crr[n].End ||
	 crr[n].Class >= limit )
    {


       n--;
       count--;
    }
  }

  FORGET_Frame();

  cdf2->ClassRangeCount = count;

  return HB_Err_Ok;

Fail:
  FREE( crr );

  return error;
}
