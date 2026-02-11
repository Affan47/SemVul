loc_viewvbpor( BePor  )

  vbpor_list *BePor;
{
  fprintf( stdout, "  > [%ld]", BePor->LINE );
  viewvexexprbound( BePor->TARGET );
  fprintf( stdout, " TYPE %s ", loc_getvbhtypename( BePor->TYPE ) );
  fprintf( stdout, " DIR  %c ", BePor->DIR );
  fprintf( stdout, " KIND %d ", BePor->KIND );
  if ( BePor->VEX != (vexexpr *)0 )
  {
    fprintf( stdout, " := " );
    viewvexexprbound( BePor->VEX );
  }
  fprintf( stdout, "\n" );
}
