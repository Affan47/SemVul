LynxIntersectInterval( Interval1, Interval2 )

  lynxinter_list *Interval1;
  lynxinter_list *Interval2;
{
  lynxinter_list  *ScanInter1;
  lynxinter_list  *ScanInter2;
  lynxinter_list  *Interval;
  lynxinter_list **PrevInter;
  lynxinter_list  *NewInter;
  char             Stop;
  long             Min;
  long             Max;

  PrevInter = &Interval;
  Interval  = (lynxinter_list *)0;

  ScanInter1 = Interval1;
  ScanInter2 = Interval2;

  while ( ScanInter1 != (lynxinter_list *)0 )
  {
    Stop = 0;

    while ( ( ScanInter2 != (lynxinter_list *)0 ) &&
            ( Stop       ==                   0 ) )
    {
      if ( ScanInter1->MAX <= ScanInter2->MIN )
      {
        Stop = 1;
      }
      else
      if ( ScanInter1->MIN < ScanInter2->MAX )
      {
        if ( ScanInter1->MAX > ScanInter2->MAX )
        {
          Max = ScanInter2->MAX;
        }
        else
        {
          Max  = ScanInter1->MAX;
          Stop = 1;
        }

        if ( ScanInter1->MIN > ScanInter2->MIN )
        {
          Min = ScanInter1->MIN;
        }
        else
        {
          Min = ScanInter2->MIN;
        }

        NewInter  =  LynxAddInterval( Min, Max );
       *PrevInter =  NewInter;
        PrevInter = &NewInter->NEXT;
      }

      if ( Stop == 0 ) ScanInter2 = ScanInter2->NEXT;
    }

    ScanInter1 = ScanInter1->NEXT;
  }

  return( Interval );
}
