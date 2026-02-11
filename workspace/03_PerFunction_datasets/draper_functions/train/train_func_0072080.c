read_buffer_bytes_available (Read_Buffer * rb)
{

  DBG (2, "read_buffer_bytes_available:\n");

  if (rb->empty)
    return rb->size;
  else if ((size_t) abs (rb->writeptr - rb->readptr) < rb->linesize)
    return 0;
  else if (rb->writeptr < rb->readptr)
    return (rb->readptr - rb->writeptr - rb->linesize);
  else
    return (rb->size + rb->readptr - rb->writeptr - rb->linesize);
}
