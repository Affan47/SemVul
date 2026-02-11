click( int num, SPoint mousePos, bool first )
{
   if ( container->getCargo().size() > num )
      unitClicked( container->getCargo()[num], mousePos, first );
   else
      unitClicked( NULL, mousePos, first );
}
