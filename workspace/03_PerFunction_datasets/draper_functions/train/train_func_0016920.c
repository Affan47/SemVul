removeCurve(size_t layer, size_t idx)
{
  Uint16 group = activationLayerList.getActivationGroup(
    graphicLayerList.getGraphicLayerName(layer), idx, OFTrue);
  if (group == 0) return EC_IllegalCall;
  activationLayerList.removeActivation(group);
  return EC_Normal;
}
