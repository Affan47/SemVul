generate_random_salt(char *salt, int length)
{
  char *buf;
  int fd, i;

  if ((fd = open("/dev/random", O_RDONLY)) < 0)
    return generate_poor_salt(salt, length);

  buf = calloc(1, length);

  if (read(fd, buf, length) != length)
  {
    close(fd);
    free(buf);

    return generate_poor_salt(salt, length);
  }

  for (i = 0; i < length; i++)
    salt[i] = saltChars[abs(buf[i]) % 64];

  close(fd);
  free(buf);

  return salt;
}
