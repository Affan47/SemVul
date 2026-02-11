ippSetOctetString(
    ipp_t           *ipp,
    ipp_attribute_t **attr,
    int             element,
    const void      *data,
    int             datalen)
{
  _ipp_value_t	*value;


  if (!ipp || !attr || !*attr || (*attr)->value_tag != IPP_TAG_STRING ||
      element < 0 || element > (*attr)->num_values ||
      datalen < 0 || datalen > IPP_MAX_LENGTH)
    return (0);


  if ((value = ipp_set_value(ipp, attr, element)) != NULL)
  {
    if ((int)((*attr)->value_tag) & IPP_TAG_CUPS_CONST)
    {


      value->unknown.data   = (void *)data;
      value->unknown.length = datalen;
    }
    else
    {


      if (value->unknown.data)
      {


	free(value->unknown.data);

	value->unknown.data   = NULL;
        value->unknown.length = 0;
      }

      if (datalen > 0)
      {
	void	*temp;

	if ((temp = malloc(datalen)) != NULL)
	{
	  memcpy(temp, data, datalen);

	  value->unknown.data   = temp;
	  value->unknown.length = datalen;
	}
	else
	  return (0);
      }
    }
  }

  return (value != NULL);
}
