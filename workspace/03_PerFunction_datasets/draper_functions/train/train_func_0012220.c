drawOpacity()
{
  State &s = iState.back();
  State &sa = iActiveState.back();
  if (s.iOpacity != sa.iOpacity) {
    sa.iOpacity = s.iOpacity;
    iStream << opacityName(s.iOpacity) << " gs\n";
  }
}
