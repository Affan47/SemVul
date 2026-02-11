ipp_col_string(ipp_t  *col,
               char   *buffer,
               size_t bufsize)
{
  char			*bufptr,
			*bufend,
			prefix = '{',
			temp[256];
  ipp_attribute_t	*attr;


  bufptr = buffer;
  bufend = buffer + bufsize - 1;

  for (attr = col->attrs; attr; attr = attr->next)
  {
    if (!attr->name)
      continue;

    if (buffer && bufptr < bufend)
      *bufptr = prefix;
    bufptr ++;
    prefix = ' ';

    if (buffer && bufptr < bufend)
      bufptr += snprintf(bufptr, bufend - bufptr + 1, "%s=", attr->name);
    else
      bufptr += strlen(attr->name) + 1;

    if (buffer && bufptr < bufend)
      bufptr += ippAttributeString(attr, bufptr, bufend - bufptr + 1);
    else
      bufptr += ippAttributeString(attr, temp, sizeof(temp));
  }

  if (prefix == '{')
  {
    if (buffer && bufptr < bufend)
      *bufptr = prefix;
    bufptr ++;
  }

  if (buffer && bufptr < bufend)
    *bufptr = '}';
  bufptr ++;

  return (bufptr - buffer);
}
