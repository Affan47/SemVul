FCEUD_SetInput (bool fourscore, bool microphone, ESI port0, ESI port1,
		ESIFC fcexp)
{
  eoptions &= ~EO_FOURSCORE;
  if (fourscore)
    {
      eoptions |= EO_FOURSCORE;
      CurInputType[0] = SI_GAMEPAD;
      CurInputType[1] = SI_GAMEPAD;
      CurInputType[2] = SIFC_NONE;
    }
  else
    {
      CurInputType[0] = port0;
      CurInputType[1] = port1;
      CurInputType[2] = fcexp;
    }

  replaceP2StartWithMicrophone = microphone;

  InitInputInterface ();
}
