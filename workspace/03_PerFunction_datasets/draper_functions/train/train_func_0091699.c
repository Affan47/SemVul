BoomBddIndex2Abl( Index )

  bddindex Index;
{
  ablexpr *Atom;
  char    *Name;

  if ( Index < BDD_INDEX_MIN )
  {
    if ( Index == BDD_INDEX_ZERO )
    {
      return( createablatom( "'0'" ) );
    }

    return( createablatom( "'1'" ) );
  }

  Index = Index - BDD_INDEX_MIN;

  if ( BoomAblIndexArray != (bddindex *)0 )
  {
    Index = BoomAblIndexArray[ Index ];
  }

  Name = BoomAblNameArray[ Index ];
  Atom = createablatom( Name );

  Name = isbddstablename( Name );

  if ( Name != (char *)0 )
  {
    ABL_CAR_L( Atom ) = addchain( (chain_list *)0, (void *)ABL_STABLE );
    addablhexpr( Atom, createablatom( Name ) );
  }

  return( Atom );
}
