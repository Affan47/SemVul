tpo_read_until_section(const char* section_name, int seek_bytes)
{
  char byte;
  unsigned int match_index = 0;
  int header_size = 0;

  while (1) {
    if (gbfread(&byte, 1, 1, tpo_file_in) < 1) {
      fatal(MYNAME ": malformed input file - attempt to read past end");
    }
    header_size++;

    if (byte == section_name[match_index]) {
      match_index++;
      if (match_index == strlen(section_name)) {

        gbfseek(tpo_file_in, seek_bytes, SEEK_CUR);
        header_size += seek_bytes;

        if (dumpheader && dumpheader[0] == '1') {
          gbfseek(tpo_file_in, -header_size, SEEK_CUR);
          tpo_dump_header_bytes(header_size);
        }
        return;

      }
    } else {
      match_index = 0;
    }
  }
}
