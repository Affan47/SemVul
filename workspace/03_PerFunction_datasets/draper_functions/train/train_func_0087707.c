VasySynopsysConvertVexEqual( VexExpr )

  vexexpr *VexExpr;
{
  if ( IsVasyDebugLevel1() )
  {
    VasyPrintf( stdout, "--> VasySynopsysConvertVexEqual\n" );
    viewvexexprboundln( VexExpr );
  }

  VexExpr = VasySynopsysConvertVexBool2( VexExpr );
  SetVexVhdlType( VexExpr, VEX_TYPE_BOOLEAN );

  if ( IsVasyDebugLevel1() )
  {
    viewvexexprboundln( VexExpr );
    VasyPrintf( stdout, "<-- VasySynopsysConvertVexEqual\n" );
  }

  return( VexExpr );
}
