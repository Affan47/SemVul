ps_print_buffer (a2ps_job * job,
		 const uchar * buffer,
		 size_t start, size_t end,
		 enum face_e face)
{
  size_t i;
  for (i = start ; i < end ; i++)
    ps_print_char (job, buffer [i], face);
}
