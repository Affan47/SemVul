ippAddBoolean(ipp_t      *ipp,
              ipp_tag_t  group,
              const char *name,
              char       value)
{
  ipp_attribute_t	*attr;


  DEBUG_printf(("ippAddBoolean(ipp=%p, group=%02x(%s), name=\"%s\", value=%d)",
                ipp, group, ippTagString(group), name, value));


  if (!ipp || !name || group < IPP_TAG_ZERO ||
      group == IPP_TAG_END || group >= IPP_TAG_UNSUPPORTED_VALUE)
    return (NULL);


  if ((attr = ipp_add_attr(ipp, name, group, IPP_TAG_BOOLEAN, 1)) == NULL)
    return (NULL);

  attr->values[0].boolean = value;

  return (attr);
}
