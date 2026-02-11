_mesa_find_line_column(const GLubyte *string, const GLubyte *pos,
                       GLint *line, GLint *col)
{
   const GLubyte *lineStart = string;
   const GLubyte *p = string;
   GLubyte *s;
   int len;

   *line = 1;

   while (p != pos) {
      if (*p == (GLubyte) '\n') {
         (*line)++;
         lineStart = p + 1;
      }
      p++;
   }

   *col = (pos - lineStart) + 1;


   while (*p != 0 && *p != '\n')
      p++;
   len = p - lineStart;
   s = malloc(len + 1);
   memcpy(s, lineStart, len);
   s[len] = 0;

   return s;
}
