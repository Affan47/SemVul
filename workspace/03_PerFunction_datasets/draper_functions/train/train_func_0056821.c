bfd_set_gp_size (bfd *abfd, unsigned int i)
{

  if (abfd->format != bfd_object)
    return;

  if (abfd->xvec->flavour == bfd_target_ecoff_flavour)
    ecoff_data (abfd)->gp_size = i;
  else if (abfd->xvec->flavour == bfd_target_elf_flavour)
    elf_gp_size (abfd) = i;
}
