deps_restore (struct deps *deps, FILE *fd, const char *self)
{
  unsigned int i, count;
  size_t num_to_read;
  size_t buf_size = 512;
  char *buf = xmalloc (buf_size);


  if (fread (&count, 1, sizeof (count), fd) != sizeof (count))
    return -1;


  for (i = 0; i < count; i++)
    {

      if (fread (&num_to_read, 1, sizeof (size_t), fd) != sizeof (size_t))
	return -1;
      if (buf_size < num_to_read + 1)
	{
	  buf_size = num_to_read + 1 + 127;
	  buf = xrealloc (buf, buf_size);
	}
      if (fread (buf, 1, num_to_read, fd) != num_to_read)
	return -1;
      buf[num_to_read] = '\0';


      if (self != NULL && strcmp (buf, self) != 0)
        deps_add_dep (deps, buf);
    }

  free (buf);
  return 0;
}
