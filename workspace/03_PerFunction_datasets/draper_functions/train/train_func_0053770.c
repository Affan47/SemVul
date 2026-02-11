LynxUnionInterval( Interval, Min, Max )

  lynxinter_list *Interval;
  long            Min;
  long            Max;
{
  lynxinter_list  *ScanInter;
  lynxinter_list  *NextInter;
  lynxinter_list  *NewInter;
  lynxinter_list  *DelInter;
  lynxinter_list **PrevInter;
  char             Stop;

  ScanInter =  Interval;
  PrevInter = &Interval;
  Stop      =  0;

  while ( ( ScanInter != (lynxinter_list *)0 ) &&
          ( Stop      ==                   0 ) )
  {
    if ( Max < ScanInter->MIN )
    {
      NewInter       = LynxAddInterval( Min, Max );
      NewInter->NEXT = *PrevInter;
     *PrevInter      = NewInter;

      Stop = 1;
    }
    else
    if ( Min > ScanInter->MAX )
    {
      PrevInter = &ScanInter->NEXT;
      ScanInter =  ScanInter->NEXT;
    }
    else
    if ( Max <= ScanInter->MAX )
    {
      if ( Min < ScanInter->MIN )
      {
        ScanInter->MIN = Min;
      }

      Stop = 1;
    }
    else
    {
      if ( Min < ScanInter->MIN )
      {
        ScanInter->MIN = Min;
      }

      ScanInter->MAX = Max;

      NextInter = ScanInter->NEXT;

      while ( NextInter != (lynxinter_list *)0 )
      {
        if ( NextInter->MAX <= Max )
        {
          ScanInter->NEXT = NextInter->NEXT;
          DelInter        = NextInter;
          NextInter       = NextInter->NEXT;

          LynxDelInterval( DelInter );
        }
        else
        {
          if ( NextInter->MIN <= Max )
          {
            ScanInter->MAX  = NextInter->MAX;
            ScanInter->NEXT = NextInter->NEXT;
            DelInter        = NextInter;

            LynxDelInterval( DelInter );
          }

          break;
        }
      }

      Stop = 1;
    }
  }

  if ( ! Stop )
  {
     NewInter  = LynxAddInterval( Min, Max );
    *PrevInter = NewInter;
  }

  return( Interval );
}
