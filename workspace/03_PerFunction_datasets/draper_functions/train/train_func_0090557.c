bfd_elf_obj_attr_size (bfd *abfd)
{
  bfd_vma size;

  size = vendor_obj_attr_size (abfd, OBJ_ATTR_PROC);
  size += vendor_obj_attr_size (abfd, OBJ_ATTR_GNU);


  return (size ? size + 1 : 0);
}
