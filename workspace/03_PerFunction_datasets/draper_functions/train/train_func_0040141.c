getShapeForTarget(const cmTarget* target)
{
  if (!target)
    {
    return "ellipse";
    }

  switch ( target->GetType() )
    {
    case cmTarget::EXECUTABLE:
      return "house";
    case cmTarget::STATIC_LIBRARY:
      return "diamond";
    case cmTarget::SHARED_LIBRARY:
      return "polygon";
    case cmTarget::MODULE_LIBRARY:
      return "octagon";
    default:
      break;
    }

  return "box";
}
