_bfd_elf_write_object_contents (bfd *abfd)
{
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);
  Elf_Internal_Shdr **i_shdrp;
  bfd_boolean failed;
  unsigned int count, num_sec;

  if (! abfd->output_has_begun
      && ! _bfd_elf_compute_section_file_positions (abfd, NULL))
    return FALSE;

  i_shdrp = elf_elfsections (abfd);

  failed = FALSE;
  bfd_map_over_sections (abfd, bed->s->write_relocs, &failed);
  if (failed)
    return FALSE;

  _bfd_elf_assign_file_positions_for_relocs (abfd);


  num_sec = elf_numsections (abfd);
  for (count = 1; count < num_sec; count++)
    {
      if (bed->elf_backend_section_processing)
	(*bed->elf_backend_section_processing) (abfd, i_shdrp[count]);
      if (i_shdrp[count]->contents)
	{
	  bfd_size_type amt = i_shdrp[count]->sh_size;

	  if (bfd_seek (abfd, i_shdrp[count]->sh_offset, SEEK_SET) != 0
	      || bfd_bwrite (i_shdrp[count]->contents, amt, abfd) != amt)
	    return FALSE;
	}
    }


  if (elf_shstrtab (abfd) != NULL
      && (bfd_seek (abfd, elf_tdata (abfd)->shstrtab_hdr.sh_offset, SEEK_SET) != 0
	  || !_bfd_elf_strtab_emit (abfd, elf_shstrtab (abfd))))
    return FALSE;

  if (bed->elf_backend_final_write_processing)
    (*bed->elf_backend_final_write_processing) (abfd,
						elf_tdata (abfd)->linker);

  if (!bed->s->write_shdrs_and_ehdr (abfd))
    return FALSE;


  if (elf_tdata (abfd)->after_write_object_contents)
    return (*elf_tdata (abfd)->after_write_object_contents) (abfd);

  return TRUE;
}
