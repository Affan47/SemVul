nowrap_type_p (tree type)
{
  if (INTEGRAL_TYPE_P (type)
      && TYPE_OVERFLOW_UNDEFINED (type))
    return true;

  if (POINTER_TYPE_P (type))
    return true;

  return false;
}
