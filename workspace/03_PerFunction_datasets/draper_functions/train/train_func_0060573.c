Load_ChainContextPos2( HB_ChainContextPosFormat2*  ccpf2,
					HB_Stream                    stream )
{
  HB_Error  error;

  HB_UShort              n, m, count;
  HB_UInt               cur_offset, new_offset, base_offset;
  HB_UInt               backtrack_offset, input_offset, lookahead_offset;

  HB_ChainPosClassSet*  cpcs;


  base_offset = FILE_Pos() - 2;

  if ( ACCESS_Frame( 2L ) )
    return error;

  new_offset = GET_UShort() + base_offset;

  FORGET_Frame();

  cur_offset = FILE_Pos();
  if ( FILE_Seek( new_offset ) ||
       ( error = _HB_OPEN_Load_Coverage( &ccpf2->Coverage, stream ) ) != HB_Err_Ok )
    return error;
  (void)FILE_Seek( cur_offset );

  if ( ACCESS_Frame( 8L ) )
    goto Fail5;

  backtrack_offset = GET_UShort();
  input_offset     = GET_UShort();
  lookahead_offset = GET_UShort();


  count = ccpf2->ChainPosClassSetCount = GET_UShort();

  FORGET_Frame();

  if ( ( error = _HB_OPEN_Load_EmptyOrClassDefinition( &ccpf2->BacktrackClassDef, 65535,
						       backtrack_offset, base_offset,
						       stream ) ) != HB_Err_Ok )
    goto Fail5;
  if ( ( error = _HB_OPEN_Load_EmptyOrClassDefinition( &ccpf2->InputClassDef, count,
						       input_offset, base_offset,
						       stream ) ) != HB_Err_Ok )
    goto Fail4;
  if ( ( error = _HB_OPEN_Load_EmptyOrClassDefinition( &ccpf2->LookaheadClassDef, 65535,
						       lookahead_offset, base_offset,
						       stream ) ) != HB_Err_Ok )
    goto Fail3;

  ccpf2->ChainPosClassSet   = NULL;
  ccpf2->MaxBacktrackLength = 0;
  ccpf2->MaxInputLength     = 0;
  ccpf2->MaxLookaheadLength = 0;

  if ( ALLOC_ARRAY( ccpf2->ChainPosClassSet, count, HB_ChainPosClassSet ) )
    goto Fail2;

  cpcs = ccpf2->ChainPosClassSet;

  for ( n = 0; n < count; n++ )
  {
    if ( ACCESS_Frame( 2L ) )
      goto Fail1;

    new_offset = GET_UShort() + base_offset;

    FORGET_Frame();

    if ( new_offset != base_offset )
    {
      cur_offset = FILE_Pos();
      if ( FILE_Seek( new_offset ) ||
	   ( error = Load_ChainPosClassSet( ccpf2, &cpcs[n],
					    stream ) ) != HB_Err_Ok )
	goto Fail1;
      (void)FILE_Seek( cur_offset );
    }
    else
    {


      ccpf2->ChainPosClassSet[n].ChainPosClassRuleCount = 0;
      ccpf2->ChainPosClassSet[n].ChainPosClassRule      = NULL;
    }
  }

  return HB_Err_Ok;

Fail1:
  for ( m = 0; m < n; m++ )
    Free_ChainPosClassSet( &cpcs[m] );

  FREE( cpcs );

Fail2:
  _HB_OPEN_Free_ClassDefinition( &ccpf2->LookaheadClassDef );

Fail3:
  _HB_OPEN_Free_ClassDefinition( &ccpf2->InputClassDef );

Fail4:
  _HB_OPEN_Free_ClassDefinition( &ccpf2->BacktrackClassDef );

Fail5:
  _HB_OPEN_Free_Coverage( &ccpf2->Coverage );
  return error;
}
