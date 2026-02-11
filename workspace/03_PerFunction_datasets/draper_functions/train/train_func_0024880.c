Load_AlternateSet( HB_AlternateSet*  as,
				    HB_Stream          stream )
{
  HB_Error error;

  HB_UShort n, count;
  HB_UShort*  a;


  if ( ACCESS_Frame( 2L ) )
    return error;

  count = as->GlyphCount = GET_UShort();

  FORGET_Frame();

  as->Alternate = NULL;

  if ( ALLOC_ARRAY( as->Alternate, count, HB_UShort ) )
    return error;

  a = as->Alternate;

  if ( ACCESS_Frame( count * 2L ) )
  {
    FREE( a );
    return error;
  }

  for ( n = 0; n < count; n++ )
    a[n] = GET_UShort();

  FORGET_Frame();

  return HB_Err_Ok;
}
