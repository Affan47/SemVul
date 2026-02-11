ippAddString(ipp_t      *ipp,
             ipp_tag_t  group,
	     ipp_tag_t  value_tag,
             const char *name,
             const char *language,
             const char *value)
{
  ipp_tag_t		temp_tag;
  ipp_attribute_t	*attr;
  char			code[IPP_MAX_LANGUAGE];


  DEBUG_printf(("ippAddString(ipp=%p, group=%02x(%s), value_tag=%02x(%s), "
                "name=\"%s\", language=\"%s\", value=\"%s\")", ipp,
		group, ippTagString(group), value_tag, ippTagString(value_tag), name,
		language, value));


  temp_tag = (ipp_tag_t)((int)value_tag & IPP_TAG_CUPS_MASK);

#if 0
  if (!ipp || !name || group < IPP_TAG_ZERO ||
      group == IPP_TAG_END || group >= IPP_TAG_UNSUPPORTED_VALUE ||
      (temp_tag < IPP_TAG_TEXT && temp_tag != IPP_TAG_TEXTLANG &&
       temp_tag != IPP_TAG_NAMELANG) || temp_tag > IPP_TAG_MIMETYPE)
    return (NULL);

  if ((temp_tag == IPP_TAG_TEXTLANG || temp_tag == IPP_TAG_NAMELANG)
          != (language != NULL))
    return (NULL);
#else
  if (!ipp || !name || group < IPP_TAG_ZERO ||
      group == IPP_TAG_END || group >= IPP_TAG_UNSUPPORTED_VALUE)
    return (NULL);
#endif


  if (language && ((int)value_tag & IPP_TAG_CUPS_CONST) &&
      strcmp(language, ipp_lang_code(language, code, sizeof(code))))
    value_tag = temp_tag;
  else if (value && value_tag == (ipp_tag_t)(IPP_TAG_CHARSET | IPP_TAG_CUPS_CONST) &&
           strcmp(value, ipp_get_code(value, code, sizeof(code))))
    value_tag = temp_tag;
  else if (value && value_tag == (ipp_tag_t)(IPP_TAG_LANGUAGE | IPP_TAG_CUPS_CONST) &&
           strcmp(value, ipp_lang_code(value, code, sizeof(code))))
    value_tag = temp_tag;


  if ((attr = ipp_add_attr(ipp, name, group, value_tag, 1)) == NULL)
    return (NULL);


  if ((int)value_tag & IPP_TAG_CUPS_CONST)
  {
    attr->values[0].string.language = (char *)language;
    attr->values[0].string.text     = (char *)value;
  }
  else
  {
    if (language)
      attr->values[0].string.language = _cupsStrAlloc(ipp_lang_code(language, code,
						      sizeof(code)));

    if (value)
    {
      if (value_tag == IPP_TAG_CHARSET)
	attr->values[0].string.text = _cupsStrAlloc(ipp_get_code(value, code,
								 sizeof(code)));
      else if (value_tag == IPP_TAG_LANGUAGE)
	attr->values[0].string.text = _cupsStrAlloc(ipp_lang_code(value, code,
								  sizeof(code)));
      else
	attr->values[0].string.text = _cupsStrAlloc(value);
    }
  }

  return (attr);
}
