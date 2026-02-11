get_good_attribute (NODE_T * p)
{
  switch (ATTRIBUTE (p)) {
  case UNIT:
  case TERTIARY:
  case SECONDARY:
  case PRIMARY:
    {
      return (get_good_attribute (SUB (p)));
    }
  default:
    {
      return (ATTRIBUTE (p));
    }
  }
}
