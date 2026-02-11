addvpnfunc( Figure, Name )

   vpnfig_list   *Figure;
   char          *Name;
{
  vpnfunc_list *Function;

  Name     = namealloc( Name );
  Function = searchvpnfunc( Figure, Name );

  if ( Function != (vpnfunc_list *)0 )
  {
    vpnerror( VPN_FUNC_EXIST_ERROR, Name, 0 );
  }

  Function = allocvpnfunc();

  Function->NAME     = Name;
  Function->LAST_ARG = &Function->ARG_DECL;
  Function->PREV     = &Figure->FUNCTION;
  Function->NEXT     = Figure->FUNCTION;

  if ( Figure->FUNCTION != (vpnfunc_list *)0 )
  {
    Figure->FUNCTION->PREV = &Function->NEXT;
  }

  Figure->FUNCTION = Function;

  addauthelem( Figure->HASH_FUNCTION, Name, (long)Function );

  return( Function );
}
