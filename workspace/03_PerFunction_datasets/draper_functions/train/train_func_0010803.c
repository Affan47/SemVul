externalGraphic(const ExternalGraphicNIC &nic)
{
  flushPendingElements();
  os() << "<external-graphic entity-system-id="
       << quot << Data(nic.entitySystemId) << quot
       << " notation-system-id="
       << quot << Data(nic.notationSystemId) << quot;
  if (nic.scaleType != symbolFalse)
    os() << " scale=" << quot << nic.scaleType << quot;
  else
    os() << " scale-x=" << quot << nic.scale[0] << quot
         << " scale-y=" << quot << nic.scale[1] << quot;
  if (nic.hasMaxWidth)
    os() << " max-width=" << quot << nic.maxWidth << quot;
  if (nic.hasMaxHeight)
    os() << " max-height=" << quot << nic.maxHeight << quot;
  if (nic.isDisplay) {
    os() << " display=" << quot << trueString << quot;
    displayNIC(nic);
  }
  else {
    if (nic.escapementDirection != symbolFalse)
      os() << " escapement-direction=" << quot << nic.escapementDirection << quot;
    if (nic.positionPointX)
      os() << " position-point-x=" << quot << nic.positionPointX << quot;
    if (nic.positionPointY)
      os() << " position-point-y=" << quot << nic.positionPointY << quot;
    inlineNIC(nic);
  }
  outputIcs();
  os() << "/>" << RE;
}
