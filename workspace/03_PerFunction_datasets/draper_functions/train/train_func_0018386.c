cat_tar(const char *name,
        int        request_id)
{
  cups_file_t	*fp;
  char		filename[1024],
		*ppdname,
		curname[256],
		buffer[8192];
  struct stat	curinfo;
  off_t		total,
		next;
  ssize_t	bytes;


  if ((fp = get_file(name, request_id, "model", filename, sizeof(filename),
                     &ppdname)) == NULL)
    return (1);


  while (read_tar(fp, curname, sizeof(curname), &curinfo))
  {
    next = cupsFileTell(fp) + ((curinfo.st_size + TAR_BLOCK - 1) &
                               ~(TAR_BLOCK - 1));

    if (!strcmp(ppdname, curname))
    {
      if (request_id)
      {
	cupsdSendIPPHeader(IPP_OK, request_id);
	cupsdSendIPPGroup(IPP_TAG_OPERATION);
	cupsdSendIPPString(IPP_TAG_CHARSET, "attributes-charset", "utf-8");
	cupsdSendIPPString(IPP_TAG_LANGUAGE, "attributes-natural-language",
			   "en-US");
	cupsdSendIPPTrailer();
      }

      for (total = 0; total < curinfo.st_size; total += bytes)
      {
        if ((size_t)(bytes = (curinfo.st_size - total)) > sizeof(buffer))
          bytes = sizeof(buffer);

        if ((bytes = cupsFileRead(fp, buffer, bytes)) < 0)
        {
          if (errno == EINTR || errno == EAGAIN)
          {
            bytes = 0;
          }
          else
          {
            perror("ERROR: [cups-driverd] Read error");
            break;
          }
        }
        else if (bytes > 0 && fwrite(buffer, bytes, 1, stdout) != 1)
          break;
      }

      cupsFileClose(fp);
      return (0);
    }

    if (cupsFileTell(fp) != next)
      cupsFileSeek(fp, next);
  }

  cupsFileClose(fp);

  fprintf(stderr, "ERROR: PPD \"%s\" not found.\n", name);

  if (request_id)
  {
    snprintf(buffer, sizeof(buffer), "PPD \"%s\" not found.", name);

    cupsdSendIPPHeader(IPP_NOT_FOUND, request_id);
    cupsdSendIPPGroup(IPP_TAG_OPERATION);
    cupsdSendIPPString(IPP_TAG_CHARSET, "attributes-charset", "utf-8");
    cupsdSendIPPString(IPP_TAG_LANGUAGE, "attributes-natural-language",
		       "en-US");
    cupsdSendIPPString(IPP_TAG_TEXT, "status-message", buffer);
    cupsdSendIPPTrailer();
  }

  return (1);
}
