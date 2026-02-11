_bfd_elf_set_arch_mach (bfd *abfd,
			enum bfd_architecture arch,
			unsigned long machine)
{


  if (arch != get_elf_backend_data (abfd)->arch
      && arch != bfd_arch_unknown
      && get_elf_backend_data (abfd)->arch != bfd_arch_unknown)
    return FALSE;

  return bfd_default_set_arch_mach (abfd, arch, machine);
}
