_assuan_funopen(void *cookie,
                cookie_read_function_t *readfn,
                cookie_write_function_t *writefn,
                cookie_seek_function_t *seekfn,
                cookie_close_function_t *closefn)
{
  cookie_io_functions_t io;

  io.read = readfn;
  io.write = writefn;
  io.seek = seekfn;
  io.close = closefn;

  return fopencookie (cookie,
		      readfn ? ( writefn ? "rw" : "r" )
		      : ( writefn ? "w" : ""), io);
}
