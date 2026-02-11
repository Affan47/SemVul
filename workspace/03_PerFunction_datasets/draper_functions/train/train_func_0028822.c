__nis_domain_of (const_nis_name name)
{
  const_nis_name cptr = strchr (name, '.');

  if (cptr == NULL)
    return "";

  if (*++cptr == '\0')
    return ".";

  return cptr;
}
