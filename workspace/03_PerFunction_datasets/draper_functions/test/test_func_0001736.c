GPS_D303_Send(UC* data, GPS_PTrack trk, int32* len, int protoid)
{
  UC* p;

  p = data;
  GPS_A300_Encode(p,trk);
  p = data+12;

  GPS_Util_Put_Float(p,trk->alt);
  p+=sizeof(float);

  if (protoid == 304) {
    GPS_Util_Put_Float(p, trk->distance_populated ? trk->distance : 1e25);
    p+=sizeof(float);
  }

  *p = trk->heartrate;
  p+=sizeof(char);

  if (protoid == 304) {
    *p = trk->cadence > 0 ? trk->cadence : 0xff;
    p+=sizeof(char);

    *p = trk->wsensor_pres;
    p+=sizeof(char);
  }

  *len = p-data;

  return;
}
