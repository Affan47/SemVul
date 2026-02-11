cbf_set_buffersize (cbf_file *file, size_t size)
{
  void * vbuffer;


  if (!file)

    return CBF_ARGUMENT;


  if (size > 0 && file->buffer_size >=  size &&
                  file->buffer_size <   2*size)

    return 0;


  vbuffer = (void *)file->buffer;

  cbf_failnez(cbf_realloc ((void **) &vbuffer,
                                &file->buffer_size, sizeof (char), size))

  file->buffer = (char *)vbuffer;

  return 0;
}
