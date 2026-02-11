EXTRACTOR_deb_extract_method (struct EXTRACTOR_ExtractContext *ec)
{
  uint64_t pos;
  int done = 0;
  const struct ObjectHeader *hdr;
  uint64_t fsize;
  unsigned long long csize;
  char buf[11];
  void *data;

  fsize = ec->get_size (ec->cls);
  if (fsize < 128)
    return;
  if (8 !=
      ec->read (ec->cls, &data, 8))
    return;
  if (0 != strncmp ("!<arch>\n", data, 8))
    return;
  pos = 8;
  while (pos + sizeof (struct ObjectHeader) < fsize)
    {
      if (pos !=
	  ec->seek (ec->cls, pos, SEEK_SET))
	return;
      if (sizeof (struct ObjectHeader) !=
	  ec->read (ec->cls, &data, sizeof (struct ObjectHeader)))
	return;
      hdr = data;
      if (0 != strncmp (&hdr->trailer[0], "`\n", 2))
        return;
      memcpy (buf, &hdr->filesize[0], 10);
      buf[10] = '\0';
      if (1 != sscanf (buf, "%10llu", &csize))
        return;
      pos += sizeof (struct ObjectHeader);
      if ((pos + csize > fsize) || (csize > fsize) || (pos + csize < pos))
        return;
      if (0 == strncmp (&hdr->name[0],
                        "control.tar.gz",
			strlen ("control.tar.gz")))
        {
	  if (0 != processControlTGZ (ec,
				      csize))
	    return;
          done++;
        }
      if (0 == strncmp (&hdr->name[0],
                        "debian-binary", strlen ("debian-binary")))
        {
	  if (0 != ec->proc (ec->cls,
			     "deb",
			     EXTRACTOR_METATYPE_MIMETYPE,
			     EXTRACTOR_METAFORMAT_UTF8,
			     "text/plain",
			     "application/x-debian-package",
			     strlen ("application/x-debian-package")+1))
	    return;
          done++;
        }
      pos += csize;
      if (2 == done)
        break;
    }
}
