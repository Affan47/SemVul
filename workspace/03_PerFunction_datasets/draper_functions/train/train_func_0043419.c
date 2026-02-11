addschboxcon( Figure, Box, Name, Type )

  schfig_list   *Figure;
  schbox_list   *Box;
  char          *Name;
  unsigned char  Type;
{
  schcon_list  *Connector;

  Connector = allocschcon();

  Connector->NAME = namealloc( Name  );

  if ( Type == SCH_CON_IN )
  {
    Connector->NEXT = Box->CON_IN;
    Box->CON_IN     = Connector;

    Box->NUMBER_IN++;
  }
  else
  {
    Connector->NEXT = Box->CON_OUT;
    Box->CON_OUT    = Connector;

    Box->NUMBER_OUT++;
  }

  if ( Type == SCH_CON_IN ) SetSchConIn( Connector );
  else                      SetSchConOut( Connector );

  SetSchConInternal( Connector );

  Connector->ROOT_TYPE = SCH_ROOT_CON_BOX;
  Connector->ROOT      = (void *)Box;

  return( Connector );
}
