elf_xtensa_merge_private_bfd_data (bfd *ibfd, bfd *obfd)
{
  unsigned out_mach, in_mach;
  flagword out_flag, in_flag;


  if (!_bfd_generic_verify_endian_match (ibfd, obfd))
    return FALSE;


  if (bfd_get_flavour (ibfd) != bfd_target_elf_flavour
      || bfd_get_flavour (obfd) != bfd_target_elf_flavour)
    return FALSE;

  out_flag = elf_elfheader (obfd)->e_flags;
  in_flag = elf_elfheader (ibfd)->e_flags;

  out_mach = out_flag & EF_XTENSA_MACH;
  in_mach = in_flag & EF_XTENSA_MACH;
  if (out_mach != in_mach)
    {
      (*_bfd_error_handler)
	(_("%B: incompatible machine type. Output is 0x%x. Input is 0x%x"),
	 ibfd, out_mach, in_mach);
      bfd_set_error (bfd_error_wrong_format);
      return FALSE;
    }

  if (! elf_flags_init (obfd))
    {
      elf_flags_init (obfd) = TRUE;
      elf_elfheader (obfd)->e_flags = in_flag;

      if (bfd_get_arch (obfd) == bfd_get_arch (ibfd)
	  && bfd_get_arch_info (obfd)->the_default)
	return bfd_set_arch_mach (obfd, bfd_get_arch (ibfd),
				  bfd_get_mach (ibfd));

      return TRUE;
    }

  if ((out_flag & EF_XTENSA_XT_INSN) != (in_flag & EF_XTENSA_XT_INSN))
    elf_elfheader (obfd)->e_flags &= (~ EF_XTENSA_XT_INSN);

  if ((out_flag & EF_XTENSA_XT_LIT) != (in_flag & EF_XTENSA_XT_LIT))
    elf_elfheader (obfd)->e_flags &= (~ EF_XTENSA_XT_LIT);

  return TRUE;
}
