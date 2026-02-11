write(IO_CACHE* file)
{
  uchar buf[APPEND_BLOCK_HEADER_LEN];
  int4store(buf + AB_FILE_ID_OFFSET, file_id);
  return (write_header(file, APPEND_BLOCK_HEADER_LEN + block_len) ||
          my_b_safe_write(file, buf, APPEND_BLOCK_HEADER_LEN) ||
	  my_b_safe_write(file, (uchar*) block, block_len));
}
