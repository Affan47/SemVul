EchoFunction (tdmInteractor I, void *data, float rot[4][4], int draw)
{
  DEFGLOBALDATA(data);
  DEFPORT(PORT_HANDLE) ;
  tdmChildGlobalP globals = _gdata;


  ENTRY(("EchoFunction (0x%x, 0x%x, 0x%x, %d)",I, data, rot, draw));

  if (draw)
    {

      _dxfDraw (globals,OBJECT,CAMERA,0);


      if (globals->CrntInteractor == globals->CursorGroup)
	{
	  tdmResumeEcho(globals->Cursor3D, tdmViewEchoMode) ;
	}
      else if (globals->CrntInteractor == globals->RoamGroup)
	{
	  tdmResumeEcho(globals->Roamer, tdmViewEchoMode) ;
	}
      else if (
	       globals->CrntInteractor == globals->RotateGroup)
	{
	  tdmResumeEcho(globals->GnomonTwirl, tdmViewEchoMode) ;
	}
    }
  else
    {

    }

  EXIT((""));
}
