next_char(glp_data *data)
{
      int c;
      if (data->c == XEOF)
         glp_sdf_error(data, "unexpected end of file\n");
      else if (data->c == '\n')
         data->count++;
      c = xfgetc(data->fp);
      if (c < 0)
      {  if (xferror(data->fp))
            glp_sdf_error(data, "read error - %s\n", xerrmsg());
         else if (data->c == '\n')
            c = XEOF;
         else
         {  glp_sdf_warning(data, "missing final end of line\n");
            c = '\n';
         }
      }
      else if (c == '\n')
         ;
      else if (isspace(c))
         c = ' ';
      else if (iscntrl(c))
         glp_sdf_error(data, "invalid control character 0x%02X\n", c);
      data->c = c;
      return;
}
