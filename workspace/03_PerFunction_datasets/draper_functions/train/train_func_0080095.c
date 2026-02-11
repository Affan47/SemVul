read_data_ascii_mmap(char *fbuf, char *buf, size_t buf_size,
                            size_t max_read, size_t *read_size)
{
  char *cptr;
  char *fptr;
  int size, ch, rd_size = 0;
  tftpd_thread *thread_ptr;
  thread_ptr = pthread_getspecific(thread_key);
  int newline = thread_ptr->newline;
  int prevchar = thread_ptr->prevchar;
  cptr = buf;
  fptr = fbuf;

  memset(buf, '\0', sizeof(char)*buf_size);
  for (size = 0; size < buf_size; size++) {
    if (newline) {
      if(prevchar == '\n')
	ch = '\n';
      else
	ch = '\0';
      newline = 0;
    }
    else {
      if (rd_size >= max_read) {
        break;
      }
      ch = *fptr; fptr++;
      if (ch == '\n' || ch == '\r') {
	prevchar = ch;
	ch = '\r';
	newline = 1;
      }
      rd_size++;
    }
    *cptr = ch;
    cptr++;
  }

  thread_ptr->newline = newline;
  thread_ptr->prevchar = prevchar;
  *read_size = rd_size;
  return size;
}
