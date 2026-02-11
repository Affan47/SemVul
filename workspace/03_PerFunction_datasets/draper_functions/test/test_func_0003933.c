MaySendMessage()
{
   return rate_limit.BytesAllowedToPut()>=256
      && Torrent::GetUDPSocket(af)->MaySendUDP();
}
