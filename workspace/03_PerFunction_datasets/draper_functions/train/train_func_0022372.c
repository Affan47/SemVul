is_tar_header (char *buf)
{
  struct tar_header *tar_hdr = (struct tar_header *) buf;
  unsigned long chksum;

  chksum = FROM_OCTAL (tar_hdr->chksum);

  if (chksum != tar_checksum (tar_hdr))
    return 0;


  if (!strncmp (tar_hdr->magic, TMAGIC, TMAGLEN - 1))
      return 2;
  return 1;
}
