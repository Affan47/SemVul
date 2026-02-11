Lookup_ChainContextSubst3( HB_GSUBHeader*               gsub,
					    HB_ChainContextSubstFormat3* ccsf3,
					    HB_Buffer                    buffer,
					    HB_UShort                     flags,
					    HB_UShort                     context_length,
					    int                           nesting_level )
{
  HB_UShort        index, i, j, property;
  HB_UShort        bgc, igc, lgc;
  HB_Error         error;

  HB_Coverage*    bc;
  HB_Coverage*    ic;
  HB_Coverage*    lc;
  HB_GDEFHeader*  gdef;


  gdef = gsub->gdef;

  if ( CHECK_Property( gdef, IN_CURITEM(), flags, &property ) )
    return error;

  bgc = ccsf3->BacktrackGlyphCount;
  igc = ccsf3->InputGlyphCount;
  lgc = ccsf3->LookaheadGlyphCount;

  if ( context_length != 0xFFFF && context_length < igc )
    return HB_Err_Not_Covered;


  if ( bgc > buffer->out_pos || buffer->in_pos + igc + lgc > buffer->in_length )
    return HB_Err_Not_Covered;

  if ( bgc )
  {


    bc       = ccsf3->BacktrackCoverage;

    for ( i = 0, j = buffer->out_pos - 1; i < bgc; i++, j-- )
    {
      while ( CHECK_Property( gdef, OUT_ITEM( j ), flags, &property ) )
      {
	if ( error && error != HB_Err_Not_Covered )
	  return error;

	if ( j + 1 == bgc - i )
	  return HB_Err_Not_Covered;
	j--;
      }

      error = _HB_OPEN_Coverage_Index( &bc[i], OUT_GLYPH( j ), &index );
      if ( error )
	return error;
    }
  }

  ic       = ccsf3->InputCoverage;

  for ( i = 0, j = buffer->in_pos; i < igc; i++, j++ )
  {

    while ( j > buffer->in_pos && CHECK_Property( gdef, IN_ITEM( j ), flags, &property ) )
    {
      if ( error && error != HB_Err_Not_Covered )
	return error;

      if ( j + igc - i + lgc == (HB_Int)buffer->in_length )
	return HB_Err_Not_Covered;
      j++;
    }

    error = _HB_OPEN_Coverage_Index( &ic[i], IN_GLYPH( j ), &index );
    if ( error )
      return error;
  }


  lc       = ccsf3->LookaheadCoverage;

  for ( i = 0; i < lgc; i++, j++ )
  {
    while ( CHECK_Property( gdef, IN_ITEM( j ), flags, &property ) )
    {
      if ( error && error != HB_Err_Not_Covered )
	return error;

      if ( j + lgc - i == (HB_Int)buffer->in_length )
	return HB_Err_Not_Covered;
      j++;
    }

    error = _HB_OPEN_Coverage_Index( &lc[i], IN_GLYPH( j ), &index );
    if ( error )
      return error;
  }

  return Do_ContextSubst( gsub, igc,
			  ccsf3->SubstCount,
			  ccsf3->SubstLookupRecord,
			  buffer,
			  nesting_level );
}
