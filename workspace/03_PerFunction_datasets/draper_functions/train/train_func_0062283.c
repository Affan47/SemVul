WriteHeader(void)
{
  size_t len;
  raw_wad_header_t header;

  switch (wad.kind)
  {
    case IWAD:
      strncpy(header.type, "IWAD", 4);
      break;

    case PWAD:
      strncpy(header.type, "PWAD", 4);
      break;
  }

  header.num_entries = UINT32(wad.num_entries);
  header.dir_start   = UINT32(wad.dir_start);

  len = fwrite(&header, sizeof(header), 1, out_file);

  if (len != 1)
    PrintWarn("Trouble writing wad header\n");
}
