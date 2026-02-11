save_uchar (CSourceData   *csource,
                               unsigned char  d)
{
     if (csource->pos > 70) {
          fprintf (csource->fp, "\"\n  \"");

          csource->pos = 3;
          csource->pad = false;
     }
     if (d < 33 || d > 126) {
          fprintf (csource->fp, "\\%o", d);
          csource->pos += 1 + 1 + (d > 7) + (d > 63);
          csource->pad = d < 64;
          return;
     }
     if (d == '\\') {
          fprintf (csource->fp, "\\\\");
          csource->pos += 2;
     }
     else if (d == '"') {
          fprintf (csource->fp, "\\\"");
          csource->pos += 2;
     }
     else if (csource->pad && d >= '0' && d <= '9') {
          fprintf (csource->fp, "\"\"%c", d);
          csource->pos += 3;
     }
     else {
          fputc (d, csource->fp);
          csource->pos += 1;
     }
     csource->pad = false;

     return;
}
