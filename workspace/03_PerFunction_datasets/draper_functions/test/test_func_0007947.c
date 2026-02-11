setRingingTone(int tone, int volume) throw(GsmException)
{
  _at->chat("^SRTC=" + intToStr(tone) + "," + intToStr(volume));
}
