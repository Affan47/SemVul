translate_addresses (bfd *abfd, char *addr_hex, FILE *f, asymbol **syms)
{
  pc = bfd_scan_vma (addr_hex, NULL, 16);
  found = FALSE;
  bfd_map_over_sections (abfd, find_address_in_section, syms);

  if (! found)
    fprintf (f, "??");
  else
    fprintf (f, "%u", line);
}
