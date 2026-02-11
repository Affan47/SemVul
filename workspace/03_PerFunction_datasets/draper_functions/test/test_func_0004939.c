Load_AlternateSubst( HB_GSUB_SubTable* st,
				      HB_Stream         stream )
{
  HB_Error error;
  HB_AlternateSubst* as = &st->alternate;

  HB_UShort          n = 0, m, count;
  HB_UInt           cur_offset, new_offset, base_offset;

  HB_AlternateSet*  aset;


  base_offset = FILE_Pos();

  if ( ACCESS_Frame( 4L ) )
    return error;

  as->SubstFormat = GET_UShort();
  new_offset      = GET_UShort() + base_offset;

  FORGET_Frame();

  cur_offset = FILE_Pos();
  if ( FILE_Seek( new_offset ) ||
       ( error = _HB_OPEN_Load_Coverage( &as->Coverage, stream ) ) != HB_Err_Ok )
    return error;
  (void)FILE_Seek( cur_offset );

  if ( ACCESS_Frame( 2L ) )
    goto Fail2;

  count = as->AlternateSetCount = GET_UShort();

  FORGET_Frame();

  as->AlternateSet = NULL;

  if ( ALLOC_ARRAY( as->AlternateSet, count, HB_AlternateSet ) )
    goto Fail2;

  aset = as->AlternateSet;

  for ( n = 0; n < count; n++ )
  {
    if ( ACCESS_Frame( 2L ) )
      goto Fail1;

    new_offset = GET_UShort() + base_offset;

    FORGET_Frame();

    cur_offset = FILE_Pos();
    if ( FILE_Seek( new_offset ) ||
	 ( error = Load_AlternateSet( &aset[n], stream ) ) != HB_Err_Ok )
      goto Fail1;
    (void)FILE_Seek( cur_offset );
  }

  return HB_Err_Ok;

Fail1:
  for ( m = 0; m < n; m++ )
    Free_AlternateSet( &aset[m] );

  FREE( aset );

Fail2:
  _HB_OPEN_Free_Coverage( &as->Coverage );
  return error;
}
