write(IO_CACHE* file)
{
  char buf[UV_NAME_LEN_SIZE];
  char buf1[UV_VAL_IS_NULL + UV_VAL_TYPE_SIZE +
	    UV_CHARSET_NUMBER_SIZE + UV_VAL_LEN_SIZE];
  uchar buf2[max(8, DECIMAL_MAX_FIELD_SIZE + 2)], *pos= buf2;
  uint unsigned_len= 0;
  uint buf1_length;
  ulong event_length;

  int4store(buf, name_len);

  if ((buf1[0]= is_null))
  {
    buf1_length= 1;
    val_len= 0;
  }
  else
  {
    buf1[1]= type;
    int4store(buf1 + 2, charset_number);

    switch (type) {
    case REAL_RESULT:
      float8store(buf2, *(double*) val);
      break;
    case INT_RESULT:
      int8store(buf2, *(longlong*) val);
      unsigned_len= 1;
      break;
    case DECIMAL_RESULT:
    {
      my_decimal *dec= (my_decimal *)val;
      dec->fix_buffer_pointer();
      buf2[0]= (char)(dec->intg + dec->frac);
      buf2[1]= (char)dec->frac;
      decimal2bin((decimal_t*)val, buf2+2, buf2[0], buf2[1]);
      val_len= decimal_bin_size(buf2[0], buf2[1]) + 2;
      break;
    }
    case STRING_RESULT:
      pos= (uchar*) val;
      break;
    case ROW_RESULT:
    default:
      DBUG_ASSERT(1);
      return 0;
    }
    int4store(buf1 + 2 + UV_CHARSET_NUMBER_SIZE, val_len);
    buf1_length= 10;
  }


  event_length= sizeof(buf)+ name_len + buf1_length + val_len + unsigned_len;

  return (write_header(file, event_length) ||
          my_b_safe_write(file, (uchar*) buf, sizeof(buf))   ||
          my_b_safe_write(file, (uchar*) name, name_len)     ||
          my_b_safe_write(file, (uchar*) buf1, buf1_length) ||
          my_b_safe_write(file, pos, val_len) ||
          my_b_safe_write(file, &flags, unsigned_len));
}
