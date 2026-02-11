getvexstdfuncid( FuncName )

  char *FuncName;
{
  authelem *Element;
  long      Index;

  if ( VexHashStdFunc == (authtable *)0 )
  {
    VexHashStdFunc = createauthtable( VEX_MAX_STD_FUNC << 1 );

    for ( Index = 0; Index < VEX_MAX_STD_FUNC; Index++ )
    {
      addauthelem( VexHashStdFunc, VEX_STD_FUNC_NAME[ Index ], Index );
    }
  }

  Element = searchauthelem( VexHashStdFunc, FuncName );

  if ( Element != (authelem *)0 ) return( Element->VALUE );

  return( -1 );
}
