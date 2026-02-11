lib3ds_io_error(Lib3dsIo *io)
{
  ASSERT(io);
  if (!io || !io->error_func) {
    return 0;
  }
  return (*io->error_func)(io->self);
}
