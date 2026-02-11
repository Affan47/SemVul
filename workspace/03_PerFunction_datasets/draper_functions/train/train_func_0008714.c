checksize(int frameid, allslitflats *slitflats)
{
  int status=0, actvals=0, unit=0, null=0, naxis=0;
  int npix[2]={0,0};
  double start[2]={0,0}, step[2]={0,0};


  if ((status = SCDRDI(frameid, "NAXIS", 1, 1, &actvals, &naxis,
               &unit, &null)) != 0) {

    return flames_midas_error(MAREMMA);
  }

  if (naxis != 2) {

    return flames_midas_error(MAREMMA);
  }

  if ((status = SCDRDI(frameid, "NPIX", 1, 2, &actvals, npix,
               &unit, &null)) != 0) {

    return flames_midas_error(MAREMMA);
  }
  uves_msg_debug("npix=%d %d",npix[0],npix[1]);
  uves_msg_debug("subcols=%d subrows=%d",slitflats->subcols,slitflats->subrows);
  if (npix[0] != slitflats->subcols || npix[1] != slitflats->subrows) {

    return flames_midas_error(MAREMMA);
  }

  if ((status = SCDRDD(frameid, "START", 1, 2, &actvals, start,
               &unit, &null)) != 0) {

    return flames_midas_error(MAREMMA);
  }
  uves_msg_debug("start[0]=%f start[1]=%f",start[0],start[1]);
  uves_msg_debug("substartx=%f substarty=%f",slitflats->substartx,slitflats->substarty);
  if (start[0] != slitflats->substartx ||
      start[1] != slitflats->substarty) {

    return flames_midas_error(MAREMMA);
  }

  if ((status = SCDRDD(frameid, "STEP", 1, 2, &actvals, step,
               &unit, &null)) != 0) {

    return flames_midas_error(MAREMMA);
  }

  if (step[0] != slitflats->substepx || step[1] != slitflats->substepy) {

    return flames_midas_error(MAREMMA);
  }

  uves_msg_debug("step[0]=%f step[1]=%f",step[0],step[1]);
  uves_msg_debug("substepx=%f substepy=%f",slitflats->substepx,slitflats->substepy);


  return(NOERR);

}
