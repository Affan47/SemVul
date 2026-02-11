new_file(void)
{
  while (242)
    {
      snprintf(filename, 100, "output-%04d.img", filename_idx++);
      if (access(filename, F_OK) != 0)
	break;

      if (filename_idx > 9999)
	{
	  printf("out of filenames!\n");
	  exit(1);
	}
    }

  if (f != NULL)
    fclose(f);

  f = fopen(filename, "wb");
  if (f == NULL)
    {
      printf("can't write file '%s'\n", filename);
      exit(1);
    }

  printf("- writing to file '%s'\n", filename);

  _lock = 1e20;
}
