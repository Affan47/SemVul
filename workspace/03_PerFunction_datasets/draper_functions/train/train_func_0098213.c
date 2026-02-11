TestCommandFraction( String )

  char *String;
{
  bddnode    *BddNode;
  char       *Scan;
  double      Fraction;

  if ( String != (char *)0 )
  {
    Scan = strchr( String, ' ' );

    if ( Scan != (char *)0 )
    {
      *Scan = '\0';
    }

    String = TestGetName( String );
    fprintf( stdout, "--> fraction %s\n", String );
    BddNode = searchbddcircuitout( (bddcircuit *)0, String );

    if ( BddNode != (bddnode *)0 )
    {
      Fraction = fractionbddnode( (bddsystem *)0, BddNode );
      fprintf( stdout, "%f\n", Fraction );
    }
    else
    {
      fprintf( stderr, "Output %s doesn't exist\n", String );
    }
  }
}
