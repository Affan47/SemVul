at_eof(stbi *s)
{
#ifndef STBI_NO_STDIO
   if (s->img_file)
      return feof(s->img_file);
#endif
   return s->img_buffer >= s->img_buffer_end;
}
