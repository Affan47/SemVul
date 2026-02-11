_dxfSetNavigateTranslateSpeed (tdmInteractor I, float speed)
{
  ENTRY(("_dxfSetNavigateTranslateSpeed(0x%x, %f)", I, speed));

  if (I)
    {
      DEFDATA(I, NavigateData) ;
      PDATA(translate_speed_factor) = speed ;
    }

  EXIT((""));
}
