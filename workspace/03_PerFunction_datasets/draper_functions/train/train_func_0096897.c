_IO_obstack_overflow (_IO_FILE *fp, int c)
{
  struct obstack *obstack = ((struct _IO_obstack_file *) fp)->obstack;
  int size;


  assert (c != EOF);
  obstack_1grow (obstack, c);


  fp->_IO_write_base = obstack_base (obstack);
  fp->_IO_write_ptr = obstack_next_free (obstack);
  size = obstack_room (obstack);
  fp->_IO_write_end = fp->_IO_write_ptr + size;

  obstack_blank_fast (obstack, size);

  return c;
}
