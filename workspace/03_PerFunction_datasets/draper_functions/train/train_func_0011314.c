GPS_Command_Send_Route(const char* port, GPS_PWay* way, int32 n)
{
  int32 ret=0;


  switch (gps_route_transfer) {
  case pA200:
    ret = GPS_A200_Send(port, way, n);
    break;
  case pA201:
    ret = GPS_A201_Send(port, way, n);
    break;
  default:
    GPS_Error("Send_Route: Unknown route protocol");
    return PROTOCOL_ERROR;
  }

  return ret;
}
