write_block (uintmax_t current_offset, size_t n_bytes,
             const char *prev_block, const char *curr_block)
{
  static bool first = true;
  static bool prev_pair_equal = false;

#define EQUAL_BLOCKS(b1, b2) (memcmp (b1, b2, bytes_per_block) == 0)

  if (abbreviate_duplicate_blocks
      && !first && n_bytes == bytes_per_block
      && EQUAL_BLOCKS (prev_block, curr_block))
    {
      if (prev_pair_equal)
        {


        }
      else
        {
          printf ("*\n");
          prev_pair_equal = true;
        }
    }
  else
    {
      size_t i;

      prev_pair_equal = false;
      for (i = 0; i < n_specs; i++)
        {
          int datum_width = width_bytes[spec[i].size];
          int fields_per_block = bytes_per_block / datum_width;
          int blank_fields = (bytes_per_block - n_bytes) / datum_width;
          if (i == 0)
            format_address (current_offset, '\0');
          else
            printf ("%*s", address_pad_len, "");
          (*spec[i].print_function) (fields_per_block, blank_fields,
                                     curr_block, spec[i].fmt_string,
                                     spec[i].field_width, spec[i].pad_width);
          if (spec[i].hexl_mode_trailer)
            {

              int field_width = spec[i].field_width;
              int pad_width = (spec[i].pad_width * blank_fields
                               / fields_per_block);
              printf ("%*s", blank_fields * field_width + pad_width, "");
              dump_hexl_mode_trailer (n_bytes, curr_block);
            }
          putchar ('\n');
        }
    }
  first = false;
}
