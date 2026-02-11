line_begin (struct log_private *priv,const char *filename,int line,const char *function,int level,const char *str)
{
   char *tmp;

   if ((tmp = prefix (priv,filename,line,function,level)) == NULL)
	 return (-1);

   if (line_append (priv,tmp) < 0)
	 {
		int saved = errno;
		mem_free (tmp);
		errno = saved;
		return (-1);
	 }

   mem_free (tmp);

   return (line_append (priv,str));
}
