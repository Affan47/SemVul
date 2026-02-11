Free_SingleSubst( HB_GSUB_SubTable* st )
{
  HB_SingleSubst*  ss = &st->single;

  switch ( ss->SubstFormat )
  {
  case 1:
    break;

  case 2:
    FREE( ss->ssf.ssf2.Substitute );
    break;

  default:
    break;
  }

  _HB_OPEN_Free_Coverage( &ss->Coverage );
}
