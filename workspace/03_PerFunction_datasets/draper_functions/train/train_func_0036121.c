ippAddBooleans(ipp_t      *ipp,
               ipp_tag_t  group,
	       const char *name,
	       int        num_values,
	       const char *values)
{
  int			i;
  ipp_attribute_t	*attr;
  _ipp_value_t		*value;


  DEBUG_printf(("ippAddBooleans(ipp=%p, group=%02x(%s), name=\"%s\", "
                "num_values=%d, values=%p)", ipp, group, ippTagString(group),
                name, num_values, values));


  if (!ipp || !name || group < IPP_TAG_ZERO ||
      group == IPP_TAG_END || group >= IPP_TAG_UNSUPPORTED_VALUE ||
      num_values < 1)
    return (NULL);


  if ((attr = ipp_add_attr(ipp, name, group, IPP_TAG_BOOLEAN, num_values)) == NULL)
    return (NULL);

  if (values)
  {
    for (i = num_values, value = attr->values;
	 i > 0;
	 i --, value ++)
      value->boolean = *values++;
  }

  return (attr);
}
