bind(const QString& node, const QString& service)
{
  if (state() != Idle)
    return false;

  if (!node.isNull())
    localResolver().setNodeName(node);
  if (!service.isNull())
    localResolver().setServiceName(service);
  return true;
}
