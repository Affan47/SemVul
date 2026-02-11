gl_truncate_buffer(GetLine *gl, int n)
{
  if(n > gl->linelen)
    return 1;
  gl->line[n] = '\0';
  gl->ntotal = n;
  return 0;
}
