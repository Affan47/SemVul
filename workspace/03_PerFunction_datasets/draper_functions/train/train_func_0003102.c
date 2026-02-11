mailimap_section_send(mailstream * fd,
    struct mailimap_section * section)
{
  int r;

  r = mailimap_char_send(fd, '[');
  if (r != MAILIMAP_NO_ERROR)
    return r;

  if (section != NULL) {
    if (section->sec_spec != NULL) {
      r = mailimap_section_spec_send(fd, section->sec_spec);
      if (r != MAILIMAP_NO_ERROR)
	return r;
    }
  }

  r = mailimap_char_send(fd, ']');
  if (r != MAILIMAP_NO_ERROR)
    return r;

  return MAILIMAP_NO_ERROR;
}
