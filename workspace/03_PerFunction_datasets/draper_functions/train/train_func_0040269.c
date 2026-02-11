loc_viewvbfor( ScanFor )

  vbfor_list  *ScanFor;
{
  fprintf( stdout, "[%ld] ", ScanFor->LINE );
  fprintf( stdout, "%s : ", ScanFor->LABEL );

  fprintf( stdout, "FOR " );
  viewvexexprbound( ScanFor->VARIABLE );
  fprintf( stdout, "IN " );

  viewvexexprbound( ScanFor->LEFT );
  if ( ScanFor->UP ) fprintf( stdout, " TO "     );
  else               fprintf( stdout, " DOWNTO " );
  viewvexexprbound( ScanFor->RIGHT );

  fprintf( stdout, "\nLOOP\n" );

  vbh_viewvbinst( ScanFor->INSTRUCTION );

  fprintf( stdout, "END LOOP %s\n", ScanFor->LABEL );
}
