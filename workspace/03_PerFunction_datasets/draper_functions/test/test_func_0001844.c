zterp_io_filesize(const zterp_io *io)
{
  if(io->type == IO_STDIO && !textmode(io))
  {
    return zterp_os_filesize(io->fp);
  }
  else
  {
    return -1;
  }
}
