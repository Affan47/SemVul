VvhVpnGetVexDeclar( VexAtom, Base, VbhType )

  vexexpr       *VexAtom;
  unsigned char  Base;
  vbtyp_list    *VbhType;
{
  char       *Name;
  vexexpr    *VexDecl;
  vexexpr    *VexArray;
  short       Left;
  short       Right;

  if ( Base != VEX_TYPE_ARRAY )
  {
    VexDecl = VvhVbhDuplicateExpr( VexAtom );
  }
  else
  {
    VexArray = VvhVbhDuplicateExpr( VexAtom );
    Name     = GetVexAtomValue( VexArray );

    VexDecl  = createvexoper( VEX_ARRAY, VexArray->WIDTH );
    addvexhexpr( VexDecl, VexArray );

    VbhType = VbhType->BASE;

    while ( ( VbhType        != (vbtyp_list *)0 ) &&
            ( ( VbhType->INDEX >= VBH_MAX_TYPE     ) ||
              ( VbhType->INDEX == VBH_TYPE_INTEGER ) ||
              ( VbhType->INDEX == VBH_TYPE_NATURAL ) ) )
    {
      if ( VbhType->INDEX == VBH_TYPE_NATURAL )
      {
        Left = 30; Right = 0;
      }
      else
      if ( VbhType->INDEX == VBH_TYPE_INTEGER )
      {
        Left = 31; Right = 0;
      }
      else
      {
        Left  = VbhType->LEFT; Right = VbhType->RIGHT;
      }

      VexArray = createvexatomvec( Name, Left, Right );
      addvexqexpr( VexDecl, VexArray );

      VbhType = VbhType->BASE;
    }
  }

  return( VexDecl );
}
