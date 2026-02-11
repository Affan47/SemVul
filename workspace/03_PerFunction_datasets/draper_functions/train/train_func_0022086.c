_HB_OPEN_Load_FeatureList( HB_FeatureList* fl,
			    HB_Stream         stream )
{
  HB_Error   error;

  HB_UShort           n, m, count;
  HB_UInt            cur_offset, new_offset, base_offset;

  HB_FeatureRecord*  fr;


  base_offset = FILE_Pos();

  if ( ACCESS_Frame( 2L ) )
    return error;

  count = fl->FeatureCount = GET_UShort();

  FORGET_Frame();

  fl->FeatureRecord = NULL;

  if ( ALLOC_ARRAY( fl->FeatureRecord, count, HB_FeatureRecord ) )
    return error;
  if ( ALLOC_ARRAY( fl->ApplyOrder, count, HB_UShort ) )
    goto Fail2;

  fl->ApplyCount = 0;

  fr = fl->FeatureRecord;

  for ( n = 0; n < count; n++ )
  {
    if ( ACCESS_Frame( 6L ) )
      goto Fail1;

    fr[n].FeatureTag = GET_ULong();
    new_offset = GET_UShort() + base_offset;

    FORGET_Frame();

    cur_offset = FILE_Pos();
    if ( FILE_Seek( new_offset ) ||
	 ( error = Load_Feature( &fr[n].Feature, stream ) ) != HB_Err_Ok )
      goto Fail1;
    (void)FILE_Seek( cur_offset );
  }

  return HB_Err_Ok;

Fail1:
  for ( m = 0; m < n; m++ )
    Free_Feature( &fr[m].Feature );

  FREE( fl->ApplyOrder );

Fail2:
  FREE( fl->FeatureRecord );

  return error;
}
