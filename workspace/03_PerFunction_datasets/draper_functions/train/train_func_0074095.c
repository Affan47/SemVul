monitor_powered_on_p (saver_info *si)
{
  Bool result;
  int event_number, error_number;
  BOOL onoff = False;
  CARD16 state;

  if (!DPMSQueryExtension(si->dpy, &event_number, &error_number))

    result = True;

  else if (!DPMSCapable(si->dpy))

    result = True;

  else
    {
      DPMSInfo(si->dpy, &state, &onoff);
      if (!onoff)

	result = True;
      else
	switch (state) {
	case DPMSModeOn:      result = True;  break;
	case DPMSModeStandby: result = False; break;
	case DPMSModeSuspend: result = False; break;
	case DPMSModeOff:     result = False; break;
	default:	      result = True;  break;
	}
    }

  return result;
}
