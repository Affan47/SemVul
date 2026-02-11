_dxfCreateZoomInteractor (tdmInteractorWin W)
{


  register tdmInteractor I ;

  ENTRY(("_dxfCreateZoomInteractor(0x%x)", W));

  if (W && (I = _dxfAllocateInteractor(W, sizeof(tdmZoomData))))
    {
      DEFDATA(I,tdmZoomData) ;


      FUNC(I, StartStroke) = StartZoomStroke ;
      FUNC(I, StrokePoint) = StrokePoint ;
      FUNC(I, DoubleClick) = NullDoubleClick ;
      FUNC(I, EndStroke) = EndZoomStroke ;
      FUNC(I, ResumeEcho) = NullResumeEcho ;
      FUNC(I, Destroy) = _dxfDeallocateInteractor ;

      EXIT(("I = 0x%x",I));
      return I ;
    }
  else
      EXIT(("ERROR"));
      return 0 ;
}
