addschfigcon( Figure, Name, Type )

  schfig_list   *Figure;
  char          *Name;
  unsigned char  Type;
{
  schcon_list  *Connector;

  Connector = allocschcon();

  Connector->NAME = namealloc( Name  );

  if ( Type == SCH_CON_IN )
  {
    Connector->NEXT = Figure->CON_IN;
    Figure->CON_IN  = Connector;

    Figure->NUMBER_IN++;
  }
  else
  {
    Connector->NEXT = Figure->CON_OUT;
    Figure->CON_OUT = Connector;

    Figure->NUMBER_OUT++;
  }

  if ( Type == SCH_CON_IN ) SetSchConIn( Connector );
  else                      SetSchConOut( Connector );

  SetSchConExternal( Connector );

  Connector->ROOT_TYPE = SCH_ROOT_CON_FIG;
  Connector->ROOT      = (void *)Figure;

  return( Connector );
}
