m_strsplit(char *str,char delim,char **array,int max_count)
{
   int i,pos = 0;
   size_t len;
   char *ptr;

   for(i=0;i<max_count;i++)
      array[i] = NULL;

   do {
      if (pos == max_count)
         goto error;

      ptr = strchr(str,delim);
      if (!ptr)
         ptr = str + strlen(str);

      len = ptr - str;

      if (!(array[pos] = malloc(len+1)))
         goto error;

      memcpy(array[pos],str,len);
      array[pos][len] = 0;

      str = ptr + 1;
      pos++;
   }while(*ptr);

   return(pos);

 error:
   for(i=0;i<max_count;i++)
      free(array[i]);
   return(-1);
}
