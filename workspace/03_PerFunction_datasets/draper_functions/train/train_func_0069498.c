_dxfCreateViewRotationInteractor (tdmInteractorWin W,
				  tdmViewEchoFunc E, tdmRotateModel M,
				  void *udata)
{


  register tdmInteractor I ;

  ENTRY(("_dxfCreateViewRotationInteractor(0x%x, 0x%x, 0x%x, 0x%x)",
	 W, E, M, udata));

  if (W && (I = _dxfAllocateInteractor (W, sizeof(tdmRotateData))))
    {
      DEFDATA(I,tdmRotateData) ;


      FUNC(I, StartStroke) = StartViewStroke ;
      FUNC(I, DoubleClick) = NullDoubleClick ;
      FUNC(I, EndStroke) = EndStroke ;
      FUNC(I, ResumeEcho) = NullResumeEcho ;
      FUNC(I, EchoFunc) = E ;
      FUNC(I, Destroy) = _dxfDeallocateInteractor ;
      FUNC(I, Config) = viewerConfig ;
      FUNC(I, restoreConfig) = NullFunction ;

      switch (M)
	{
	case tdmXYPlaneRoll:
	  FUNC(I, StrokePoint) = ViewRoll ;
	  break ;
	case tdmZTwirl:
	default:
	  FUNC(I, StrokePoint) = Twirl ;
	  break ;
	}


      UDATA(I) = udata ;

      EXIT((""));
      return I ;
    }
  else
      EXIT(("ERROR"));
      return 0 ;
}
