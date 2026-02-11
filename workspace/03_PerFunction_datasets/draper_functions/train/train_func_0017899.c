gmon_get_ptr_signedness ()
{
  int sext;


  sext = bfd_get_sign_extend_vma (core_bfd);
  if (sext == -1)
    return ptr_unsigned;
  return (sext ? ptr_signed : ptr_unsigned);
}
