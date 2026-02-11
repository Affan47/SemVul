create_disk_file(FILE *f)
{
  for (int c = 0;c < 80;c++)
    for (int h = 0;h < 2;h++)
      for (int s = 1;s < 6;s++)
	if (!write_sector(f, c, h, s))
	  return false;

  return true;
}
