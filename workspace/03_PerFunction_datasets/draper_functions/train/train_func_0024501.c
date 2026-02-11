help_new_node(const char   *filename,
              const char   *anchor,
	      const char   *section,
	      const char   *text,
	      time_t       mtime,
              off_t        offset,
	      size_t       length)
{
  help_node_t	*n;


  DEBUG_printf(("2help_new_node(filename=\"%s\", anchor=\"%s\", text=\"%s\", "
                "mtime=%ld, offset=%ld, length=%ld)", filename, anchor, text,
                (long)mtime, (long)offset, (long)length));

  n = (help_node_t *)calloc(1, sizeof(help_node_t));
  if (!n)
    return (NULL);

  n->filename = strdup(filename);
  n->anchor   = anchor ? strdup(anchor) : NULL;
  n->section  = (section && *section) ? strdup(section) : NULL;
  n->text     = strdup(text);
  n->mtime    = mtime;
  n->offset   = offset;
  n->length   = length;

  return (n);
}
