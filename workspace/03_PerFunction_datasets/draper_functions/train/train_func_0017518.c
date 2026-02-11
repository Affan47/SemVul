ippContainsInteger(
    ipp_attribute_t *attr,
    int             value)
{
  int		i;
  _ipp_value_t	*avalue;


  if (!attr)
    return (0);

  if (attr->value_tag != IPP_TAG_INTEGER && attr->value_tag != IPP_TAG_ENUM &&
      attr->value_tag != IPP_TAG_RANGE)
    return (0);


  if (attr->value_tag == IPP_TAG_RANGE)
  {
    for (i = attr->num_values, avalue = attr->values; i > 0; i --, avalue ++)
      if (value >= avalue->range.lower && value <= avalue->range.upper)
        return (1);
  }
  else
  {
    for (i = attr->num_values, avalue = attr->values; i > 0; i --, avalue ++)
      if (value == avalue->integer)
        return (1);
  }

  return (0);
}
