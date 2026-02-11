gl_read_char(GetLine *gl)
{
  int retval;


  int was_masked = gl->signals_masked;


  if(!gl) {
    errno = EINVAL;
    return EOF;
  };


  if(!was_masked && gl_mask_signals(gl, &gl->old_signal_set))
    return EOF;


  retval = _gl_read_char(gl);


  if(!was_masked)
    gl_unmask_signals(gl, &gl->old_signal_set);
  return retval;
}
