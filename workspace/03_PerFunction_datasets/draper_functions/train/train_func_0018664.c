__libc_open64 (const char *file, int oflag, ...)
{
  int mode = 0;

  if (oflag & O_CREAT)
    {
      va_list arg;
      va_start (arg, oflag);
      mode = va_arg (arg, int);
      va_end (arg);
    }

  if (SINGLE_THREAD_P)
    return INLINE_SYSCALL (open, 3, file, oflag | O_LARGEFILE, mode);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int result = INLINE_SYSCALL (open, 3, file, oflag | O_LARGEFILE, mode);

  LIBC_CANCEL_RESET (oldtype);

  return result;
}
