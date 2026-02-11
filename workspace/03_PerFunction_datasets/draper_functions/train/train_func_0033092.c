viewrtldecl( Decl )

  rtldecl_list *Decl;
{
  rtlsym *DeclSym;
  int     Scan;
  int     Width;

  fprintf( stdout, "\n--> Declaration" );

  fprintf( stdout, "\n\t\tVEX_ATOM : " );
  viewvexexprbound( Decl->VEX_ATOM );

  fprintf( stdout, "\n\t\tVEX_INIT : " );
  viewvexexprbound( Decl->VEX_INIT );

  fprintf( stdout, "\n\t\tDECL_SYM :\n" );

  DeclSym = Decl->DECL_SYM;
  Width   = Decl->VEX_ATOM->WIDTH;

  for ( Scan = 0; Scan < Width; Scan++ )
  {
    viewrtlsym( &DeclSym[ Scan ] );
  }

  if ( Decl->DIR >= RTL_MAX_DIR_TYPE )
  {
    fprintf( stdout, "\n\t\tDIR   : %d", (int)Decl->DIR  );
  }
  else
  {
    fprintf( stdout, "\n\t\tDIR   : %s", RTL_DIR_TYPE[ Decl->DIR ] );
  }

  if ( Decl->TYPE >= RTL_MAX_DECLAR_TYPE )
  {
    fprintf( stdout, "\n\t\tTYPE  : %d", Decl->TYPE  );
  }
  else
  {
    fprintf( stdout, "\n\t\tTYPE  : %s", RTL_DECLAR_TYPE[ Decl->TYPE ] );
  }

  if ( Decl->BASE >= VEX_MAX_TYPE )
  {
    fprintf( stdout, "\n\t\tBASE  : %d", Decl->BASE );
  }
  else
  {
    fprintf( stdout, "\n\t\tBASE  : %s", VEX_TYPE_NAME[ Decl->BASE ] );
  }

  if ( Decl->KIND >= RTL_MAX_KIND_TYPE )
  {
    fprintf( stdout, "\n\t\tKIND  : %d", Decl->KIND );
  }
  else
  {
    fprintf( stdout, "\n\t\tKIND  : %s", RTL_KIND_TYPE[ Decl->KIND ] );
  }

  fprintf( stdout, "\n\t\tFLAGS : %lx", Decl->FLAGS );
  fprintf( stdout, "\n\t\tUSER  : %lx", (long)Decl->USER );
  fprintf( stdout, "\n<-- Declaration" );
}
