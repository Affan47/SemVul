VasySimplifyHashDefineAsg( RtlFigure )

  rtlfig_list *RtlFigure;
{
  rtldecl_list  *RtlDeclar;
  rtlsym        *RtlSymbol;
  rtlasg_list   *RtlAsg;
  vexexpr       *VexAtom;
  char          *AtomName;
  int            VexMin;
  int            VexMax;
  int            VexIndex;

  if ( VasyHashRtlAsg == (authtable *)0 )
  {
    VasyHashRtlAsg = createauthtable( 1000 );
  }
  else
  {
    resetauthtable( VasyHashRtlAsg );
  }

  for ( RtlAsg  = RtlFigure->ASSIGN;
        RtlAsg != (rtlasg_list *)0;
        RtlAsg  = RtlAsg->NEXT )
  {
    VexAtom   = RtlAsg->VEX_ATOM;
    AtomName  = GetVexAtomValue( VexAtom );
    RtlDeclar = searchrtldecl( RtlFigure, AtomName );

    VexMin   = getvexvectormin( VexAtom );
    VexMax   = getvexvectormax( VexAtom );

    if ( ( RtlAsg->TYPE    == RTL_ASG_COMBINATORIAL ) &&
         ( RtlDeclar->TYPE == RTL_DECLAR_SIGNAL     ) &&
         ( IsVasyRtlDeclarDefine( RtlDeclar )       ) )
    {
      SetVasyRtlAssignSubst( RtlAsg );

      for ( VexIndex = VexMin; VexIndex <= VexMax; VexIndex++ )
      {
        RtlSymbol = getrtlsymdecl( RtlDeclar, VexIndex );

        addauthelem( VasyHashRtlAsg, (char *)RtlSymbol, (long)RtlAsg );
      }
    }
  }
}
