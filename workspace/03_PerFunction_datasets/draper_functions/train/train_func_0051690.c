skipfile(int fd, size_t size)
{
  ssize_t rc;
  size_t ar;
  char array[512];
  ar = 0;

  while(ar != size)
    {
      rc = readall(fd, array, (size-ar < 512 ? size - ar : 512));
      if(rc < 0)
        {
	  printf("readmtcp skipfile: error %d skipping checkpoint\n", errno);
	  exit(1);
        }
      else if(rc == 0)
        {
	  printf("readmtcp skipfile: only skipped %zu bytes instead of %zu from"
                 " checkpoint file\n",
                 ar, size);
	  exit(1);
        }

      ar += rc;
    }
}
