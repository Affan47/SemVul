GetPair(char *buf, int buf_len, char *key, char *value, char **tail)
{
   int i=0, j;

   key[0] = 0;
   value[0] = 0;

   if (buf[i] == '#')
   {
      for (; buf[i] != '\n' && i < buf_len; i++);
      if (buf[i] == '\n')
         i++;
   }

   j = 0;
   while ((buf[i] != '=') && (i < buf_len) && (j < UTILS_LINE_SIZE))
      key[j++] = buf[i++];
   for (j--; key[j] == ' ' && j > 0; j--);
   key[++j] = 0;

   if (buf[i] == '=')
      for (i++; buf[i] == ' ' && i < buf_len; i++);

   j = 0;
   while ((buf[i] != '\n') && (i < buf_len) && (j < UTILS_LINE_SIZE))
      value[j++] = buf[i++];
   for (j--; value[j] == ' ' && j > 0; j--);
   value[++j] = 0;

   if (buf[i] == '\n')
     i++;

   if (tail != NULL)
      *tail = buf + i;

   return i;
}
