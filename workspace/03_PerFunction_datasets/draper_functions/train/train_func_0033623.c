punchLiteralPool( LPOOL_T *p, WORD32 lpool_page )
{
  WORD32  loc;
  WORD32  pageno;
  WORD32  tmplc;

  pageno  = GET_PAGE (lpool_page);
  lpool_page &= 07600;

  if(( lpool_page == 0 ) && ( p != &pz ))
  {
    return;
  }

  if( lit_loc[pageno] < lit_base[pageno] )
  {
    if( !rim_mode )
    {

		punchOrigin( lit_loc[pageno] | lpool_page );
	 }

    for( loc = lit_loc[pageno]; loc < lit_base[pageno]; loc++ )
    {
      tmplc = loc + lpool_page;
      printLine( line, (field | tmplc), p->pool[loc], LOC_VAL );
      punchLocObject( tmplc, p->pool[loc] );
    }
    p->error = FALSE;
    lit_base[pageno] = lit_loc[pageno];
  }
}
