sprnt_fp (struct string_buffer *buf, mpfr_srcptr p,
          const struct printf_spec spec)
{
  int length;
  struct number_parts np;

  length = partition_number (&np, p, spec);
  if (length < 0)
    return -1;


  if (np.pad_type == LEFT && np.pad_size != 0)
    buffer_pad (buf, ' ', np.pad_size);


  if (np.sign)
    buffer_pad (buf, np.sign, 1);


  if (np.prefix_ptr)
    buffer_cat (buf, np.prefix_ptr, np.prefix_size);


  if (np.pad_type == LEADING_ZEROS && np.pad_size != 0)
    buffer_pad (buf, '0', np.pad_size);


  MPFR_ASSERTN (np.ip_ptr != NULL);
  if (MPFR_UNLIKELY (np.thousands_sep))
    buffer_sandwich (buf, np.ip_ptr, np.ip_size, np.ip_trailing_zeros,
                     np.thousands_sep);
  else
    {
      buffer_cat (buf, np.ip_ptr, np.ip_size);


      if (np.ip_trailing_zeros != 0)
        buffer_pad (buf, '0', np.ip_trailing_zeros);
    }


  if (np.point)
    buffer_pad (buf, np.point, 1);


  if (np.fp_leading_zeros != 0)
    buffer_pad (buf, '0', np.fp_leading_zeros);


  if (np.fp_ptr)
    buffer_cat (buf, np.fp_ptr, np.fp_size);


  if (np.fp_trailing_zeros != 0)
    buffer_pad (buf, '0', np.fp_trailing_zeros);


  if (np.exp_ptr)
    buffer_cat (buf, np.exp_ptr, np.exp_size);


  if (np.pad_type == RIGHT && np.pad_size != 0)
    buffer_pad (buf, ' ', np.pad_size);

  clear_string_list (np.sl);
  return length;
}
