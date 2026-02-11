loc_addctldecl( Figure, Expr, DeclType )

  ctlfig_list   *Figure;
  vexexpr       *Expr;
  unsigned char  DeclType;
{
  ctldecl_list  *Decl;
  ctldecl_list **PrevDecl;
  vexexpr       *Atom;
  ctlsym        *Sym;
  char          *Name;
  int            Width;
  int            Index;
  int            IndexStep;
  int            Scan;

  if ( ! IsVexNodeAtom( Expr ) )
  {
    Atom = getvexarrayatom( Expr );
  }
  else
  {
    Atom = Expr;
  }

  Name = GetVexAtomValue( Atom );

  if ( ( DeclType <= CTL_DECLAR_ALL      ) ||
       ( DeclType >= CTL_MAX_DECLAR_TYPE ) )
  {
    ctlerror( CTL_UNKNOWN_DECLAR_TYPE, DeclType, Name );
  }

  Decl = allocctldecl();

  Width = Atom->WIDTH;
  Sym   = allocctlsym( Width );

  if ( ( ! IsVexNodeVarWidth( Atom ) ) &&
       ( IsVexAtomVector( Atom )     ) )
  {
    Index     = Atom->LEFT;
    IndexStep = IsVexAtomDown( Atom ) ? -1 : 1;
  }
  else
  {
    Index     = -1;
    IndexStep = 0;
  }

  for ( Scan = 0; Scan < Width; Scan++ )
  {
    Sym[ Scan ].NAME  = Name;
    Sym[ Scan ].INDEX = Index;
    Sym[ Scan ].DECL  = Decl;

    Index += IndexStep;
  }

  PrevDecl = &Figure->DECLAR[ DeclType ];

  Decl->VEX_ATOM  = Expr;
  Decl->DECL_SYM  = Sym;
  Decl->DECL_TYPE = DeclType;
  Decl->PREV      = &Figure->DECLAR[ DeclType ];
  Decl->NEXT      = *(Decl->PREV);

  if ( Decl->NEXT != (ctldecl_list *)0 )
  {
    Decl->NEXT->PREV = &Decl->NEXT;
  }

  *(Decl->PREV) = Decl;

  addauthelem( Figure->HASH_DECLAR[ DeclType       ], Name, (long)Decl );
  addauthelem( Figure->HASH_DECLAR[ CTL_DECLAR_ALL ], Name, (long)Decl );

  return( Decl );
}
