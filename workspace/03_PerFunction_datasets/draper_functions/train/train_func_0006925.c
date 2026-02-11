OnBtnClear( wxCommandEvent & roEvtCmd )
{
  CpntNgsIndSrc  oCpntIndSrc;

  oCpntIndSrc.bClear( );
  SetValues( oCpntIndSrc );
}
