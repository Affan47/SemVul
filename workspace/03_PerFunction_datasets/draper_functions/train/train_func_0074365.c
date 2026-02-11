Free_ReverseChainContextSubst( HB_GSUB_SubTable* st )
{
  HB_UShort      n, count;
  HB_ReverseChainContextSubst*  rccs = &st->reverse;

  HB_Coverage*  c;

  _HB_OPEN_Free_Coverage( &rccs->Coverage );

  if ( rccs->LookaheadCoverage )
  {
    count = rccs->LookaheadGlyphCount;
    c     = rccs->LookaheadCoverage;

    for ( n = 0; n < count; n++ )
      _HB_OPEN_Free_Coverage( &c[n] );

    FREE( c );
  }

  if ( rccs->BacktrackCoverage )
  {
    count = rccs->BacktrackGlyphCount;
    c     = rccs->BacktrackCoverage;

    for ( n = 0; n < count; n++ )
      _HB_OPEN_Free_Coverage( &c[n] );

    FREE( c );
  }

  FREE ( rccs->Substitute );
}
