iovec_read (struct bfd *nbfd ATTRIBUTE_UNUSED,
			    void *stream, void *buf, file_ptr nbytes,
			    file_ptr offset)
{
  FILE* file = (FILE*) stream;

  if (fseek(file, offset, SEEK_SET) != 0)
    die ("fseek error");

  return fread (buf, 1, nbytes, file);
}
