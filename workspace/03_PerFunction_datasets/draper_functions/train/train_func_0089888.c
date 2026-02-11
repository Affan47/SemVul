_bfd_set_gp_value (bfd *abfd, bfd_vma v)
{
  if (! abfd)
    abort ();
  if (abfd->format != bfd_object)
    return;

  if (abfd->xvec->flavour == bfd_target_ecoff_flavour)
    ecoff_data (abfd)->gp = v;
  else if (abfd->xvec->flavour == bfd_target_elf_flavour)
    elf_gp (abfd) = v;
}
