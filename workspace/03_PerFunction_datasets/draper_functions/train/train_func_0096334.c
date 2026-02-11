fsp_ver_fixup (fsp_link *link, int sock)
{
  if (link->hash_type != FS_HASH_UNKNOWN) {

    return 0;
  }

  unsigned char *out = message_new(FS_NO_OP, 0, 0);
  write(sock, out, FS_HEADER + 0);
  free(out);

  unsigned char header[FS_HEADER];
  int err = recv(sock, header, FS_HEADER, MSG_WAITALL);

  if (err < 0) {
    fs_error(LOG_ERR, "recv header from socket failed, %s", strerror(errno));
    return -1;
  } else if (err == 0) {
    return -1;
  }

  switch (header[2]) {
    case 0x80:
      link->hash_type = FS_HASH_MD5;
      break;
    case 0x81:
      link->hash_type = FS_HASH_CRC64;
      break;
    case 0x82:
      link->hash_type = FS_HASH_UMAC;
      break;

    default:
      fs_error(LOG_ERR, "incompatible protocol");
      return -1;
  }

  if (fsp_vermagic[2] == header[2]) {


    unsigned int * const l = (unsigned int *) (header + 4);
    char *buffer = calloc(1, *l);
    recv(sock, buffer, *l, MSG_WAITALL);
    free(buffer);
    return 0;
  } else {
    fsp_vermagic[2] = header[2];
    return 1;
  }
}
