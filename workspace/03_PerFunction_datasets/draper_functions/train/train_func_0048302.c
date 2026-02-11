viewvexexprfile( VexFile, Expr )

  FILE    *VexFile;
  vexexpr *Expr;
{
  VexViewFile     = VexFile;
  VexViewLength   = 0;
  VexViewFunction = loc_viewvexfile;

  if ( Expr != (vexexpr *)0 ) loc_viewvex( Expr );
}
