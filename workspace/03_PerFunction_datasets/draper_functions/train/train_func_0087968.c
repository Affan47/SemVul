BoomBehOptimizeGradient( BehFigure )

  befig_list *BehFigure;
{
  beaux_list    *BehAux;
  boombefiginfo *FigInfo;
  long           Cost;
  long           NewCost;
  long           Iteration;
  long           Amplitude;
  long           MaxIteration;
  long           MaxAmplitude;
  chain_list    *BestOrder;
  chain_list    *NewOrder;
  int            Level;

  FigInfo = GetBoomBehFigInfo( BehFigure );
  MaxIteration = FigInfo->ITERATION;
  MaxAmplitude = FigInfo->AMPLITUDE;
  Level        = FigInfo->OPTIM_LEVEL;

  if ( MaxIteration <= 0 ) MaxIteration = 2;
  if ( MaxAmplitude <= 0 ) MaxAmplitude = 5;

  BehAux     = BoomBehComputeAux( BehFigure, BehFigure->BEAUX );
  Cost       = BoomBehGiveCost( BehFigure );
  BestOrder  = BoomBehGetBddOrder( BehFigure );

  if ( IsBoomDebugLevel0() )
  {
    BoomPrintf( stdout, "Initial cost %ld\n", Cost );
  }

  MaxIteration = MaxIteration * (Level + 1);

  if ( ( FigInfo->VERBOSE ) &&
       ( ! BoomDebugFlag  ) )
  {
    fprintf( stdout, "\t--> Optimization %% 0\b" );
    fflush( stdout );
  }

  for ( Iteration = 0; Iteration < MaxIteration; Iteration++ )
  {
    if ( IsBoomDebugLevel0() )
    {
      BoomPrintf( stdout, "Iteration %ld\n", Iteration );
    }

    Amplitude = MaxAmplitude;

    do
    {
      if ( IsBoomDebugLevel0() )
      {
        BoomPrintf( stdout, "Amplitude %ld\n", Amplitude );
      }

      BoomBehRandomBddOrder( BehFigure, Amplitude );

      NewOrder = BoomBehGradientBddOrder( BehFigure );

      BehAux  = BoomBehComputeAux( BehFigure, BehAux );
      NewCost = BoomBehGiveCost( BehFigure );

      if ( IsBoomDebugLevel0() )
      {
        BoomPrintf( stdout, "NewCost: %ld\n", NewCost );
      }

      if ( NewCost < Cost )
      {
        Cost = NewCost;

        freechain( BestOrder );
        BestOrder = NewOrder;
      }
      else
      {
        freechain( NewOrder );
      }

      Amplitude--;
    }
    while ( Amplitude > 0 );

    if ( ( FigInfo->VERBOSE ) &&
         ( ! BoomDebugFlag  ) )
    {
      fprintf( stdout, "%-3ld\b\b\b", ( ( Iteration + 1 ) * 100 ) / MaxIteration );
      fflush( stdout );
    }
  }

  if ( FigInfo->VERBOSE )
  {
    fprintf( stdout, "\n\n" );
  }

  if ( IsBoomDebugLevel0() )
  {
    BoomPrintf( stdout, "Best cost : %ld\n", Cost );
  }

  BoomBehRebuildBddNode( BehFigure, BestOrder );

  BehAux = BoomBehComputeAux( BehFigure, BehAux );
  Cost   = BoomBehGiveCost( BehFigure );

  if ( IsBoomDebugLevel0() )
  {
    BoomPrintf( stdout, "Final cost %ld\n", Cost );
  }
}
