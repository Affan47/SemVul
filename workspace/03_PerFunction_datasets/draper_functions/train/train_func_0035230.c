lseek(Bit64s offset, int whence)
{
  if ((offset % 512) != 0)
    BX_PANIC(("lseek HD with offset not multiple of 512"));
  BX_DEBUG(("concat_image_t.lseek(%d)", whence));

  if (offset < thismin) {

    for (int i=index-1; i>=0; i--) {
      if (offset >= start_offset_table[i]) {
	index = i;
	fd = fd_table[i];
	thismin = start_offset_table[i];
	thismax = thismin + length_table[i] - 1;
	BX_DEBUG(("concat_image_t.lseek to earlier image, index=%d", index));
	break;
      }
    }
  } else if (offset > thismax) {

    for (int i=index+1; i<maxfd; i++) {
      if (offset < start_offset_table[i] + length_table[i]) {
	index = i;
	fd = fd_table[i];
	thismin = start_offset_table[i];
	thismax = thismin + length_table[i] - 1;
	BX_DEBUG(("concat_image_t.lseek to earlier image, index=%d", index));
	break;
      }
    }
  }

  offset -= start_offset_table[index];
  if (offset < 0 || offset >= length_table[index]) {
    BX_PANIC(("concat_image_t.lseek to byte %ld failed", (long)offset));
    return -1;
  }

  seek_was_last_op = 1;
  return (Bit64s)::lseek(fd, (off_t)offset, whence);
}
