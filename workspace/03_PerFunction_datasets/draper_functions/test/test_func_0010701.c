make_qualified_name (struct archive_info * arch,
		     struct archive_info * nested_arch,
		     const char *member_name)
{
  size_t len;
  char * name;

  len = strlen (arch->file_name) + strlen (member_name) + 3;
  if (arch->is_thin_archive && arch->nested_member_origin != 0)
    len += strlen (nested_arch->file_name) + 2;

  name = (char *) malloc (len);
  if (name == NULL)
    {
      error (_("Out of memory\n"));
      return NULL;
    }

  if (arch->is_thin_archive && arch->nested_member_origin != 0)
    snprintf (name, len, "%s[%s(%s)]", arch->file_name,
	      nested_arch->file_name, member_name);
  else if (arch->is_thin_archive)
    snprintf (name, len, "%s[%s]", arch->file_name, member_name);
  else
    snprintf (name, len, "%s(%s)", arch->file_name, member_name);

  return name;
}
