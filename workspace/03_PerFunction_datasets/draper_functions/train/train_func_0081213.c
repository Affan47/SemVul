aboxmbkrds( FigureMbk, FigureRds )

   phfig_list  *FigureMbk;
   rdsfig_list *FigureRds;
{
  rdsrec_list *Rectangle;
  long         XAB1;
  long         XAB2;
  long         YAB1;
  long         YAB2;

  XAB1 = RfmRoundLow( FigureMbk->XAB1 * RDS_LAMBDA / SCALE_X );
  XAB2 = RfmRoundLow( FigureMbk->XAB2 * RDS_LAMBDA / SCALE_X );
  YAB1 = RfmRoundHigh( FigureMbk->YAB1 * RDS_LAMBDA / SCALE_X );
  YAB2 = RfmRoundHigh( FigureMbk->YAB2 * RDS_LAMBDA / SCALE_X );

  if ( ( XAB1 != 0 ) || ( XAB2 != 0 ) ||
       ( YAB1 != 0 ) || ( YAB2 != 0 ) )
  {
    Rectangle =

      addrdsfigrec( FigureRds, FigureMbk->NAME,
                    RDS_ABOX,
                    XAB1, YAB1, XAB2 - XAB1, YAB2 - YAB1 );

    SetRdsFigure( Rectangle );

    Rectangle->USER = (void *)Rectangle;

    return( Rectangle );
  }

  return( (rdsrec_list *)NULL );
}
