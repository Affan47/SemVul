viewvexexprstr( Expr )

  vexexpr *Expr;
{
  if ( VexStringBuffer == (char *)0 )
  {
    VexStringBuffer = (char *)autallocblock( VEX_STRING_BUFFER_SIZE );
    VexStringSize   = VEX_STRING_BUFFER_SIZE;
  }

  VexStringLength = 0;
  VexStringBuffer[ 0 ] = '\0';

  VexViewLength   = 0;
  VexViewFunction = loc_viewvexstr;

  if ( Expr != (vexexpr *)0 ) loc_viewvex( Expr );

  return( VexStringBuffer );
}
