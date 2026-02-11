StartStroke (tdmInteractor I, int x, int y, int btn, int s)
{
  tdmInteractor btn1, btn2, btn3 ;

  ENTRY(("StartStroke(0x%x, %d, %d, %d)",
	 I, x, y, btn));


  btn1 = BTN1(I) ;
  btn2 = BTN2(I) ;
  btn3 = BTN3(I) ;


  switch(btn)
    {
    case 1:
      *I = *BTN1(I) ;
      break ;
    case 2:
      *I = *BTN2(I) ;
      break ;
    default:
      *I = *BTN3(I) ;
      break ;
    }


  tdmStartStroke (I, x, y, btn, s) ;


  BTN1(I) = btn1 ;
  BTN2(I) = btn2 ;
  BTN3(I) = btn3 ;
  IS_GROUP(I) = 1 ;

  FUNC(I, StartStroke) = StartStroke ;
  FUNC(I, Destroy) = Destroy ;

  EXIT((""));
}
