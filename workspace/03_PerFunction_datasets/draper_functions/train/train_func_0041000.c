loc_viewvbgnr( BeGnr )

  vbgnr_list *BeGnr;
{
  vbins_list *BeIns;
  vbpcs_list *BePcs;

  fprintf( stdout, "  > [%ld]\n", BeGnr->LINE );

  if ( BeGnr->LABEL != (char *)0 )
  {
    fprintf( stdout, "LABEL : %s\n", BeGnr->LABEL );
  }

  fprintf( stdout, "TYPE  : %x\n", (int)BeGnr->TYPE );

  if ( BeGnr->TYPE == VBH_GENERATE_IF )
  {
    fprintf( stdout, "IF (" );
    viewvexexprbound( BeGnr->IF_COND );
    fprintf( stdout, ")" );
  }
  else
  {
    fprintf( stdout, "FOR " );
    viewvexexprbound( BeGnr->FOR_VARIABLE );
    fprintf( stdout, " IN " );

    viewvexexprbound( BeGnr->FOR_LEFT );
    if ( BeGnr->FOR_UP ) fprintf( stdout, " TO "     );
    else                 fprintf( stdout, " DOWNTO " );
    viewvexexprbound( BeGnr->FOR_RIGHT );
  }

  fprintf( stdout, "\nGENERATE\n" );

  fprintf( stdout, "BEINS\n" );

  for ( BeIns  = BeGnr->BEINS;
        BeIns != (vbins_list *)0;
        BeIns  = BeIns->NEXT )
  {
    loc_viewvbins( BeIns );
  }

  fprintf( stdout, "BEPCS\n" );

  for ( BePcs  = BeGnr->BEPCS;
        BePcs != (vbpcs_list *)0;
        BePcs  = BePcs->NEXT )
  {
    loc_viewvbpcs( BePcs );
  }

  fprintf( stdout, "BEGNR\n" );

  for ( BeGnr  = BeGnr->BEGNR;
        BeGnr != (vbgnr_list *)0;
        BeGnr  = BeGnr->NEXT )
  {
    loc_viewvbgnr( BeGnr );
  }

  fprintf( stdout, "\nEND GENERATE\n" );
}
