finish_default (void)
{
  if (!link_info.relocatable)
    _bfd_fix_excluded_sec_syms (link_info.output_bfd, &link_info);
}
