_bfd_elf_eh_frame_present (struct bfd_link_info *info)
{
  asection *eh = bfd_get_section_by_name (info->output_bfd, ".eh_frame");

  if (eh == NULL)
    return FALSE;


  for (eh = eh->map_head.s; eh != NULL; eh = eh->map_head.s)
    if (eh->size > 8)
      return TRUE;

  return FALSE;
}
