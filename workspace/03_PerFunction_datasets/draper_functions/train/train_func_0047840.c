lua_reportbug (char *s)
{
 char msg[1024];
 strcpy (msg, s);
 if (lua_debugline != 0)
 {
  int i;
  if (nfuncstack > 0)
  {
   sprintf (strchr(msg,0),
         "\n\tin statement begining at line %d in function \"%s\" of file \"%s\"",
         lua_debugline, s_name(funcstack[nfuncstack-1].function),
  	 lua_file[funcstack[nfuncstack-1].file]);
   sprintf (strchr(msg,0), "\n\tactive stack\n");
   for (i=nfuncstack-1; i>=0; i--)
    sprintf (strchr(msg,0), "\t-> function \"%s\" of file \"%s\"\n",
                            s_name(funcstack[i].function),
			    lua_file[funcstack[i].file]);
  }
  else
  {
   sprintf (strchr(msg,0),
         "\n\tin statement begining at line %d of file \"%s\"",
         lua_debugline, lua_filename());
  }
 }
 lua_error (msg);
}
